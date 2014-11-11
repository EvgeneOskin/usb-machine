#include "usbtool.h"

UsbTool::UsbTool() {
    int status = libusb_init(&this->usbContex);
    std::cout << "status is " << status;
}

UsbTool::~UsbTool() {
    libusb_exit(usbContex);
}

QList<QString>* UsbTool::getDevices() {
    libusb_device **devList = NULL;
    size_t count = libusb_get_device_list(this->usbContex, &devList);
    for(size_t i = 0; i < count; i++) {
        libusb_device *device = devList[i];
    }
    return new QList<QString>();
}
