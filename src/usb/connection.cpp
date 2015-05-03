#include "connection.h"

UsbConnection::UsbConnection(QObject *parent) :
    QObject(parent), handler(NULL), is_busy(false) {

    libusb_init(&context);
    libusb_set_debug(NULL, 3);
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
                qCritical("Can not open device.\n");
            }
            device = list[i];
            libusb_ref_device (device);
            break;
        }
    }
    libusb_free_device_list(list, 1);
    if (handler) {
        initInterfaceAndMaxPackageSize();
//        print_info();
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

void resetByteArray(uint8_t array[], size_t size, uint8_t value) {
    memset (array, value, size);
}

int isSupporrtedInterfaceDesc(libusb_interface_descriptor *interface) {
    return interface->bInterfaceClass == 0x0A &&
            interface->bInterfaceSubClass == 0x00 &&
            interface->bInterfaceProtocol == 0x00;
}

ConnectionStatus UsbConnection::initInterfaceAndMaxPackageSize() {
    libusb_config_descriptor *config_desc;
    int error_config = libusb_get_active_config_descriptor(device, &config_desc);
    if (error_config) {
        qCritical("Error get config. s\n", libusb_error_name(error_config));
        return access_denied;
    }
    for (int i_interface = 0; i_interface < config_desc->bNumInterfaces; i_interface++) {
        for (int i_altinterface = 0;
             i_altinterface < config_desc->interface[i_interface].num_altsetting;
            i_altinterface++) {
            libusb_interface_descriptor alt_settings = config_desc->interface[i_interface].altsetting[i_altinterface];
            if (isSupporrtedInterfaceDesc(&alt_settings)) {
                this->interface = i_interface;
                this->altSettings = i_altinterface;
                libusb_endpoint_descriptor ep_desc = alt_settings.endpoint[0];
                this->maxPackageSize = ep_desc.wMaxPacketSize;
            }
        }
    }
    libusb_free_config_descriptor(config_desc);
    config_desc = NULL;
    return ready;
}

ConnectionStatus UsbConnection::sendFrames(DataFormatter &formatter) {
    int error = 0;

    qDebug("Activating interfaces, %d", interface);
    error = libusb_claim_interface(handler, interface);
    if (error) {
        qCritical("Error set interface. %s\n", libusb_error_name(error));
        return access_denied;
    }

    uint8_t * bytesToSend = new uint8_t[maxPackageSize];
    uint8_t * recivedBytes = new uint8_t[maxPackageSize];
    size_t packageCount = formatter.getPackageCount();
    qDebug("PackageCount: %d", packageCount);
    for (size_t i = 0; i < packageCount; i++) {
        int dataSize = formatter.format(i, bytesToSend, maxPackageSize);
        int actualLength = 0;
        error = libusb_bulk_transfer(handler, CDC_OUT_EP, bytesToSend, dataSize, &actualLength, 0);
        if (!error && actualLength == dataSize) {
            qDebug("Package %d, transfered dize: %d", i, actualLength);
        } else {
            qCritical("Can not send data LIBUSB_ENDPOINT_OUT. %s\n", libusb_error_name(error));
            delete[] bytesToSend;
            return access_denied;
        }

        resetByteArray(bytesToSend, dataSize, 0x00);

        error = libusb_bulk_transfer(handler, CDC_IN_EP, recivedBytes, maxPackageSize, &actualLength, 0);
        if (!error) {
            qDebug("Recieved data size: %d", actualLength);
        } else {
            qCritical("Can not send data LIBUSB_ENDPOINT_IN. %s\n", libusb_error_name(error));
        }
        resetByteArray(recivedBytes, maxPackageSize, 0x00);
    }
    delete[] bytesToSend;
    delete[] recivedBytes;

//    bool waitForReponse = true;
//    while (waitForReponse) {
//        int actualLength = 0;
//        error = libusb_bulk_transfer(handler, CDC_IN_EP, recivedBytes, maxPackageSize, &actualLength, 0);
//        if (!error) {
//            qDebug("Recieved data size: %d", actualLength);
//        } else {
//            qCritical("Can not send data LIBUSB_ENDPOINT_IN. %s\n", libusb_error_name(error));
//        }
//        resetByteArray(recivedBytes, maxPackageSize, 0x00);
//        waitForReponse = false;
//    }

    libusb_release_interface(handler, interface);
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

    unsigned char data[255] = {};
    int response = libusb_get_string_descriptor_ascii (handler, desc.iProduct, data, sizeof(data));
    qDebug("Product Description: %s|\n", data);
    response = libusb_get_string_descriptor_ascii (handler, desc.iManufacturer, data, sizeof(data));
    qDebug("Manufacturer Description: %s|\n", data);
    libusb_get_string_descriptor_ascii (handler, desc.iSerialNumber, data, sizeof(data));
    qDebug("SerialNumber Description: %s|\n", data);

    qDebug("\nbegin descriptor\n");
    qDebug("\tport: %d\n", libusb_get_port_number(device));
    qDebug("\tbus_num: %d\n", libusb_get_bus_number(device));
    qDebug("\taddress: %d\n", libusb_get_device_address(device));
    qDebug("\tspeed: %d\n", libusb_get_device_speed(device));
    qDebug("\tClass: %d\n", desc.bDeviceClass);
    qDebug("\tSubClass: %d\n", desc.bDeviceSubClass);
    qDebug("\tDeviceProtocol: %d\n", desc.bDeviceProtocol);
    qDebug("\tidVendor: %d\n", desc.idVendor);
    qDebug("\tidProduct: %d\n", desc.idProduct);
    qDebug("\tiManufacturer: %d\n", desc.iManufacturer);
    qDebug("\tiProduct: %d\n", desc.iProduct);
    qDebug("\tiSerialNumber: %d\n", desc.iSerialNumber);
    qDebug("\tbMaxPacketSize0: %d\n", desc.bMaxPacketSize0);
    qDebug("\tbNumConfigurations: %d\n", desc.bNumConfigurations);
    qDebug("\tconfigDescriptor:\n");


    error_config = libusb_get_active_config_descriptor(device, &config_desc);
    if (error_config) {
        if (error_config == LIBUSB_ERROR_NOT_FOUND) {
            qDebug("Error config not founds\n");
        } else {
            qDebug("Error in config %s\n", libusb_error_name (error_config));
        }
    } else {
        qDebug("\tiConfiguration: %d\n", config_desc->iConfiguration);
        qDebug("\tbNumInterface: %d\n", config_desc->bNumInterfaces);
        qDebug("\tbmAttributes: %d\n", config_desc->bmAttributes);
        for (int i_interface = 0; i_interface < config_desc->bNumInterfaces; i_interface++) {
            for (int i_altinterface = 0;
                 i_altinterface < config_desc->interface[i_interface].num_altsetting;
                i_altinterface++) {
                libusb_interface_descriptor alt_settings = config_desc->interface[i_interface].altsetting[i_altinterface];
                qDebug("\tbInterfaceNumber[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceNumber);
                qDebug("\tbInterfaceClass[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceClass);
                qDebug("\bInterfaceSubClass[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceSubClass);
                qDebug("\tbInterfaceProtocol[%d][%d]: %d\n", i_interface, i_altinterface,
                    alt_settings.bInterfaceProtocol);
                qDebug("\textra[%d][%d]: %s\n", i_interface, i_altinterface,
                    alt_settings.extra);
                for (int i_ep = 0; i_ep < alt_settings.bNumEndpoints; i_ep++) {
                    libusb_endpoint_descriptor ep_desc = alt_settings.endpoint[i_ep];
                    qDebug("\t\tbEndpointAddress[%d][%d][%d]: %d (in=%d / out=%d)\n",
                        i_interface, i_altinterface, i_ep,
                        ep_desc.bEndpointAddress, LIBUSB_ENDPOINT_IN, LIBUSB_ENDPOINT_OUT);
                    qDebug("\t\tbDescriptorType[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.bDescriptorType);
                    qDebug("\t\tbmAttributes[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                           ep_desc.bmAttributes);
                    qDebug("\t\textra[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.extra_length);
                    qDebug("\t\tbSynchAddress[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                        ep_desc.bSynchAddress);
                }
            }
        }
        libusb_free_config_descriptor(config_desc);
    }
}
