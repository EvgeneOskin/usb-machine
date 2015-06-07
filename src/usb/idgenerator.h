#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include "inttypes.h"

class IdGenerator
{
public:
    IdGenerator();
    ~IdGenerator();
    uint16_t generate();
private:
    uint16_t id;

};

#endif // IDGENERATOR_H
