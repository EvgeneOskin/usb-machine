#include "axisrange.h"
#include <algorithm>

AxisRange::AxisRange(double down, double up) {

    this->down = std::min(down, up);
    this->up = std::max(up, down);
    diff = up - down;
}

AxisRange::~AxisRange() {}

uint16_t AxisRange::setPositionInRange(double value) {
    if (!diff || value > up) {
        return 0xFFFF;
    } else if (value < down) {
        return 0;
    } else {
        return round((value - down)/diff*0xffff);
    }
}
