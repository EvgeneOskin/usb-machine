#ifndef DATAFORMATTER
#define DATAFORMATTER

#include "usbmesaagetypes.h"

class DataFormatter {

public:
    virtual size_t getPackageCount() = 0;
    virtual size_t format(size_t index, uint8_t pureData[], size_t maxSize) = 0;
};

#endif // DATAFORMATTER

