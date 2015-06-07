#include "trackdataformatter.h"

TrackDataFormatter::TrackDataFormatter(
        lines_t *lines, TYPE_VECTOR(double) maxVelocity,
        TYPE_VECTOR(uint16_t) coordinateScale, TYPE_VECTOR(uint16_t) velocityScale,
        TYPE_VECTOR(AxisRangePtr) ranges, QObject *parent) :
    QObject(parent),
    modelingWrapper(lines, maxVelocity, coordinateScale, velocityScale, ranges) {

    splineCount = modelingWrapper.getUsbSplineMessagesCount();
    pointsCount = modelingWrapper.getUsbPointMessagesCount();
    packageCount = 1 +  // setup Package
            splineCount +
            pointsCount +
            1 // start Package
            ;
}

TrackDataFormatter::~TrackDataFormatter() {}

size_t TrackDataFormatter::format(size_t packageIndex, uint8_t pureData[], size_t maxSize) {
    if (modelingWrapper.hasError()) {
        return 0;
    }

    return notSafeFormatFrame(packageIndex, pureData);
}

size_t TrackDataFormatter::getPackageCount () {
    return packageCount;
}

size_t TrackDataFormatter::notSafeFormatFrame(size_t packageIndex, uint8_t pureData[]) {
    size_t size = GENERAL_MESSAGE_HEADER_SIZE();
    if (packageIndex == 0) {
        modelingWrapper.copySetupMessageData ((message_t*) pureData);
        size += message_setup_size();
    } else if (packageIndex < splineCount + 1) {
        modelingWrapper.copySplineMessageData (
                    packageIndex - 1, (message_t*) pureData);
        size += message_spline_size();
    } else if (packageIndex < splineCount + pointsCount + 1) {
        modelingWrapper.copyPointMessageData (
                    packageIndex - splineCount - 1, (message_t*) pureData);
        size += message_track_point_size();
    } else {
        modelingWrapper.copyStartMessageData ((message_t*) pureData);
        size += message_start_size ();
    }

    return size;
}

