#ifndef USBCONNECTION_H
#define USBCONNECTION_H

#include <QObject>
#include "libusb.h"
#include "dataformatter.h"


#define VENDOR_ID 0x0483
#define PRODUCT_ID 0x5740

#define CDC_IN_EP                       0x81  /* EP1 for data IN */
#define CDC_OUT_EP                      0x01  /* EP1 for data OUT */
#define CDC_CMD_EP                      0x82  /* EP2 for CDC commands */
#define MAX_SEND_BYTES 65536


typedef enum {
    ready,
    disconnected,
    access_denied,
    busy
} ConnectionStatus;


class UsbConnection : public QObject
{
    Q_OBJECT
public:
    UsbConnection(QObject *parent = 0);
    ~UsbConnection();

    void print_info();

    ConnectionStatus usb_connect();
    ConnectionStatus usb_disconnect();
    ConnectionStatus getStatus();
    ConnectionStatus sendFrames(DataFormatter &formatter);
    std::string getProductDescription();
    std::string getManufactorerDescription();

private:
    libusb_context *context;
    libusb_device *device;
    libusb_device_handle *handler;
    bool is_busy;

    ConnectionStatus initInterfaceAndMaxPackageSize();
    int interface;
    int altSettings;
    size_t maxPackageSize;

signals:

public slots:

};

#endif // USBCONNECTION_H
