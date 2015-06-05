#ifndef TRACKMODELINGWRAPPER_H
#define TRACKMODELINGWRAPPER_H

#include "modeling/abstracttrack.h"
#include "idgenerator.h"
#include "usbmesaagetypes.h"

// Defined in parser/spline.h spline_nodes_t;

typedef std::list<message_spline_node_t> usb_spline_nodes_t;

typedef std::pair<uint16_t, usb_spline_nodes_t> spline_map_node_t;
typedef std::map<uint16_t, usb_spline_nodes_t> spline_map_t;


class TrackModelingWrapper : public AbstractTrack
{
public:
    TrackModelingWrapper(
            lines_t *lines,
            TYPE_VECTOR(double) maxVelocity,
            TYPE_VECTOR(uint16_t) coordinateScale,
            TYPE_VECTOR(uint16_t) velocityScale,
            TYPE_VECTOR(AxisRangePtr) ranges);
    ~TrackModelingWrapper();

    size_t getUsbSplineMessagesCount();
    void copySplineMessageData(size_t index, message_t *message);

    size_t getUsbPointMessagesCount();
    void copyPointMessageData(size_t index, message_t *message);

    void copySetupMessageData(message_t *message);
    void copyStartMessageData(message_t *message);

    bool hasError();

private:
    TYPE_VECTOR(uint16_t) coordinateScale;
    TYPE_VECTOR(uint16_t) velocityScale;

    uint8_t errorCode;

    IdGenerator splineIdGenrator;
    IdGenerator messageIdGenerator;
    spline_map_t splines;
    std::vector <track_point_t> points;
};

#endif // TRACKMODELINGWRAPPER_H
