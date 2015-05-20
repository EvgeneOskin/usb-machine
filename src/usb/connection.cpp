#include "connection.h"
#include "stdio.h"

UsbConnection::UsbConnection(QObject *parent) :
    QObject(parent), handler(NULL), is_busy(false) {

    libusb_init(&context);
    libusb_set_debug(context, 2);
}

UsbConnection::~UsbConnection() {
    if (handler || device) {
        usb_disconnect ();
    }
    libusb_exit(context);
}

ConnectionStatus UsbConnection::usb_connect() {
    libusb_device **list = NULL;
    ssize_t size_devices = libusb_get_device_list(context, &list);
    for (int i = 0; i < size_devices; i++) {
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(list[i], &desc);

        if (desc.idVendor == VENDOR_ID && desc.idProduct == PRODUCT_ID) {
            int error = libusb_open(list[i], &handler);

            if (error) {
                printf("Can not open device.\n");
            }
            device = list[i];
            libusb_ref_device (device);
            break;
        }
    }
    libusb_free_device_list(list, 1);
    if (handler) {
        return ready;
    } else {
        return disconnected;
    }
}

ConnectionStatus UsbConnection::usb_disconnect() {
    libusb_close(handler);
    libusb_unref_device (device);
    device = NULL;
    handler = NULL;
    return disconnected;
}

ConnectionStatus UsbConnection::getStatus() {
    if (handler == NULL) {
        return disconnected;
    } else if (is_busy){
        return busy;
    } else {
        return ready;
    }
}

void resetByteArray(byte array[], size_t size, byte value) {
    for (size_t i = 0; i < size; i++) {
        array[i] = value;
    }
}

ConnectionStatus UsbConnection::sendFrames(DataFormatter &formatter) {
    byte * bytesToSend = new byte[MAX_SEND_BYTES];
    size_t framesCount = formatter.getFrameCount();
    int dataSize = 0;
    int error = 0;
    int interface = 0;
    libusb_config_descriptor *config_desc;

    error = libusb_get_active_config_descriptor(device, &config_desc);

    for (int i_interface = 0; i_interface < config_desc->bNumInterfaces; i_interface++) {
        interface = i_interface;
    }
    libusb_free_config_descriptor(config_desc);

    error = libusb_claim_interface(handler, interface);

    if (error) {
        printf("Error set interface.\n");
        return access_denied;
    }

    for (size_t i = 0; i < framesCount; i++) {
        dataSize = formatter.formatFrame(i, bytesToSend, MAX_SEND_BYTES);

        int actualLength = 0;

        error = libusb_interrupt_transfer(handler, CDC_OUT_EP, bytesToSend, dataSize, &actualLength, 0);
        if (!error && actualLength == dataSize) {
            // results of the transaction can now be found in the data buffer
            // parse them here and report button press
            printf("Transfered: {");
            for (size_t transfered_i = 0; transfered_i < actualLength; transfered_i++) {
                printf("%x, ", *(bytesToSend + transfered_i));
            }
            printf("}\n");
        } else {
            printf("Can not send data LIBUSB_ENDPOINT_OUT. %d\n", error);
        }
        resetByteArray(bytesToSend, MAX_SEND_BYTES, 0x00);

        actualLength = 0;
        error = libusb_interrupt_transfer(handler, CDC_IN_EP, bytesToSend, MAX_SEND_BYTES, &actualLength, 0);
        if (!error) {
            // results of the transaction can now be found in the data buffer
            // parse them here and report button press
            printf("Recieved: {");
            for (size_t recieved_i = 0; recieved_i < actualLength; recieved_i++) {
                printf("%x, ", *(bytesToSend + recieved_i));
            }
            printf("}\n");
        } else {
            printf("Can not send data LIBUSB_ENDPOINT_IN. %d\n", error);
        }

        resetByteArray(bytesToSend, MAX_SEND_BYTES, 0x00);
    }

    libusb_release_interface(handler, interface);
    delete[] bytesToSend;

    return ready;
}

std::string UsbConnection::getProductDescription() {
    char data[255] = {};
    int response;
    libusb_device_descriptor desc;
    if (device && handler){
        libusb_get_device_descriptor(device, &desc);
        response = libusb_get_string_descriptor_ascii (
                    handler, desc.iProduct, (unsigned char*)data, 255);
    }
    return std::string(data);
}

std::string UsbConnection::getManufactorerDescription() {
    char data[255] = {};
    int response;
    libusb_device_descriptor desc;
    if (device && handler){
        libusb_get_device_descriptor(device, &desc);
        response = libusb_get_string_descriptor_ascii (
                handler, desc.iManufacturer, (unsigned char*)data, 255);
    }
    return std::string(data);
}

void UsbConnection::print_info() {
    int error_config;
    libusb_config_descriptor *config_desc;
    libusb_device_descriptor desc;
    if (!device) {
        ConnectionStatus status = usb_connect ();
        if (status == ready){
            return;
        }
    }
    libusb_get_device_descriptor(device, &desc);

    //if (error_config) {
    //    continue;
    //}
    unsigned char data[255] = {};
    int response = libusb_get_string_descriptor_ascii (handler, desc.iProduct, data, sizeof(data));
    printf("Product Description: %s|\n", response, data);
    response = libusb_get_string_descriptor_ascii (handler, desc.iManufacturer, data, sizeof(data));
    printf("Manufacturer Description: %s|\n", response, data);
    libusb_get_string_descriptor_ascii (handler, desc.iSerialNumber, data, sizeof(data));
    printf("SerialNumber Description: %s|\n", response, data);

    printf("\nbegin descriptor\n");
    printf("\tport: %d\n", libusb_get_port_number(device));
    printf("\tbus_num: %d\n", libusb_get_bus_number(device));
    printf("\taddress: %d\n", libusb_get_device_address(device));
    printf("\tspeed: %d\n", libusb_get_device_speed(device));
    printf("\tClass: %d\n", desc.bDeviceClass);
    printf("\tSubClass: %d\n", desc.bDeviceSubClass);
    printf("\tDeviceProtocol: %d\n", desc.bDeviceProtocol);
    printf("\tidVendor: %d\n", desc.idVendor);
    printf("\tidProduct: %d\n", desc.idProduct);
    printf("\tiManufacturer: %d\n", desc.iManufacturer);
    printf("\tiProduct: %d\n", desc.iProduct);
    printf("\tiSerialNumber: %d\n", desc.iSerialNumber);
    printf("\tbMaxPacketSize0: %d\n", desc.bMaxPacketSize0);
    printf("\tbNumConfigurations: %d\n", desc.bNumConfigurations);
    printf("\tconfigDescriptor:\n");


    error_config = libusb_get_active_config_descriptor(device, &config_desc);
    if (error_config) {
        if (error_config == LIBUSB_ERROR_NOT_FOUND) {
            printf("Error config not founds\n");
        } else {
            printf("Error in config %d\n", error_config);
        }
    } else {

        printf("\tiConfiguration: %d\n", config_desc->iConfiguration);
        printf("\tbNumInterface: %d\n", config_desc->bNumInterfaces);
        printf("\tbmAttributes: %d\n", config_desc->bmAttributes);
        for (int i_interface = 0; i_interface < config_desc->bNumInterfaces; i_interface++) {
            for (int i_altinterface = 0;
                 i_altinterface < config_desc->interface[i_interface].num_altsetting;
                i_altinterface++) {
                libusb_interface_descriptor alt_settings = config_desc->interface[i_interface].altsetting[i_altinterface];
                printf("\tbInterfaceClass[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceClass);

                printf("\tbInterfaceNumber[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceNumber);
                printf("\tbInterfaceProtocol[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceProtocol);
                printf("\textra[%d][%d]: %s\n", i_interface, i_altinterface,
                    alt_settings.extra);
                for (int i_ep = 0; i_ep < alt_settings.bNumEndpoints; i_ep++) {
                    libusb_endpoint_descriptor ep_desc = alt_settings.endpoint[i_ep];
                    printf("\t\tbEndpointAddress[%d][%d][%d]: %d (in=%d / out=%d)\n",
                        i_interface, i_altinterface, i_ep,
                        ep_desc.bEndpointAddress, LIBUSB_ENDPOINT_IN, LIBUSB_ENDPOINT_OUT);
                    printf("\t\tbDescriptorType[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.bDescriptorType);
                    printf("\t\tbmAttributes[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.bmAttributes);
                    printf("\t\textra[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.extra_length);
                    printf("\t\tbSynchAddress[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.bSynchAddress);
                }
            }
        }
        libusb_free_config_descriptor(config_desc);
    }
}
