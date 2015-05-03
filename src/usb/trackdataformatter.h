#ifndef TRACKDATAFORMATTER_H
#define TRACKDATAFORMATTER_H

#include <QObject>
#include "dataformatter.h"
#include "usbmesaagetypes.h"
#include "parser/parsertypes.h"
#include "trackmodelingwrapper.h"


class TrackDataFormatter : public QObject, public DataFormatter {

    Q_OBJECT
public:
    TrackDataFormatter(
            lines_t *lines,
            TYPE_VECTOR(double) maxVelocity,
            TYPE_VECTOR(uint16_t) coordinateScale,
            TYPE_VECTOR(uint16_t) velocityScale,
            TYPE_VECTOR(AxisRangePtr) ranges,
            QObject *parent=0);
    ~TrackDataFormatter();
    size_t format(size_t index, uint8_t pureData[], size_t maxSize);
    size_t getPackageCount();
    size_t calculateSize();
private:
    TrackModelingWrapper modelingWrapper;
    size_t packageCount;
    size_t splineCount;
    size_t pointsCount;

    size_t notSafeFormatFrame(size_t packageIndex, uint8_t pureData[]);
};

#endif // TRACKDATAFORMATTER_H
