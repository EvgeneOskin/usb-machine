#ifndef AXISRANGE_H
#define AXISRANGE_H

#include <QObject>

typedef unsigned char byte;

class AxisRange : public QObject {

    Q_OBJECT
public:
    AxisRange(double down, double up, QObject *parent = 0);
    virtual ~AxisRange();
    bool setPositionInRange(double value, byte* byte2Array);

private:
    double down;
    double up;
    double diff;

};

#endif // AXISRANGE_H
