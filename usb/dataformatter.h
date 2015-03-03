#ifndef DATAFORMATTER
#define DATAFORMATTER

#include "usbtypes.h"

class DataFormatter {

public:

    virtual size_t formatFrame(
            size_t frameIndex, byte pureData[], size_t maxSize) = 0;
    virtual size_t getFrameCount() = 0;
};

#endif // DATAFORMATTER

