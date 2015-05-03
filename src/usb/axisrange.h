#ifndef AXISRANGE_H
#define AXISRANGE_H

#include "inttypes.h"

class AxisRange{

public:
    AxisRange(double down, double up);
    virtual ~AxisRange();
    uint16_t setPositionInRange(double value);

private:
    double down;
    double up;
    double diff;

};

#endif // AXISRANGE_H
