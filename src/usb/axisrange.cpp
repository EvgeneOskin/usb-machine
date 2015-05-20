#include "math.h"
#include "axisrange.h"

AxisRange::AxisRange(double down, double up, QObject *parent)
    : QObject(parent) {

    this->down = std::min(down, up);
    this->up = std::max(up, down);
    diff = up - down;
}

AxisRange::~AxisRange() {}

bool AxisRange::setPositionInRange(double value, byte* byte2Array) {
    if (down < value && value < up) {
        short b2 = round((value - down)/diff*0xffff);
        byte2Array[0] = (byte) b2 & 0xff;
        byte2Array[1] = (byte) (b2 >> 8) & 0xff;
        return true;
    } else if (value < down) {
        byte2Array[0] = 0x00;
        byte2Array[1] = 0x00;
        return false;
    } else {
        byte2Array[0] = 0xff;
        byte2Array[1] = 0xff;
        return false;
    }
}
