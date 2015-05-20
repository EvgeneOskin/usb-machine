#ifndef TRACKDATAFORMATTER_H
#define TRACKDATAFORMATTER_H

#include <QObject>
#include "dataformatter.h"
#include "usbtypes.h"
#include "parser/parsertypes.hpp"
#include <inttypes.h>

#define MESSAGE_TYPE_TRACK_POINT 1
#define MESSAGE_TYPE_TRACK_ACC 2
#define MESSAGE_TYPE_SPLINE 3
#define MESSAGE_TYPE_SETUP 4

#define TRACK_POINT_TYPE_VALUE 0
#define TRACK_POINT_TYPE_SPLINE 1

typedef struct {
    uint16_t x;
    uint16_t y;
} message_spline_node_t;

typedef struct {
    uint8_t message_type;
    uint16_t massage_id;
    uint16_t message_size;
    union {
        struct {
            uint8_t point_id;
            uint8_t x_type;
            uint16_t x_value;
            uint8_t y_type;
            uint16_t y_value;
            uint8_t z_type;
            uint16_t z_value;
        } track_point_data;
        struct {
            uint8_t spline_id;
            uint8_t spline_size;
            message_spline_node_t* nodes;
        } spline_data;
        struct {
            uint16_t x_scale;
            uint16_t x_velocity_scale;
            uint16_t y_scale;
            uint16_t y_velocity_scale;
            uint16_t z_scale;
            uint16_t z_velocity_scale;
        } setup_data;
        struct {
            uint8_t point_id;
        } track_point_acc_data;
    } message_data;
} message_t;



class TrackDataFormatter : public QObject, public DataFormatter {

    Q_OBJECT
public:
    TrackDataFormatter(
            frames_t &hiLevelFrames,
            axis_ranges_t &ranges,
            QObject *parent=0);
    ~TrackDataFormatter();
    size_t formatFrame(size_t frameIndex, byte pureData[], size_t maxSize);
    size_t getFrameCount();

private:
    frames_t hiLevelFrames;
    axis_ranges_t ranges;
    std::list<std::string> varsStr;

    size_t calculateFrameSize(frame_t frame);
    size_t calculateValueSize(Value &value);

    size_t headerSize();
    size_t notSafeFormatFrame(size_t frameSize, frame_t frame, byte pureData[]);
    size_t addValue(AxisRange *axisRange, Value &value, byte *pureData);
};

#endif // TRACKDATAFORMATTER_H
