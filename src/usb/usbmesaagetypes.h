#ifndef USBMESSAGETYPES_H
#define USBMESSAGETYPES_H

#include "axisrange.h"

#include "parser/parser_value.h"
#include "modeling/modelingvectortypes.h"
#include <inttypes.h>
#include <memory>

#define TRACK_POINT_TYPE_VALUE 0
#define TRACK_POINT_TYPE_SPLINE 1


typedef struct {
    uint16_t type;
    uint16_t value;
} usb_point_coordinate_t;
DECLARE_VECTOR(usb_point_coordinate_t)

typedef struct {
    uint16_t scale;
    uint16_t velocity_scale;
} usb_setup_coordinate_t;
DECLARE_VECTOR(usb_setup_coordinate_t)


typedef struct {
    uint16_t point_id;
    TYPE_VECTOR(usb_point_coordinate_t) coordinates;
} track_point_t;

#define MESSAGE_TYPE_TRACK_POINT 1
#define MESSAGE_TYPE_TRACK_ACC 2
#define MESSAGE_TYPE_SPLINE 3
#define MESSAGE_TYPE_SETUP 4
#define MESSAGE_TYPE_START 5

#define MAX_SPLINE_NODE_COUNT 0xFF

typedef struct {
    uint16_t x;
    uint16_t y;
} message_spline_node_t;

typedef struct {
    uint16_t spline_id;
    message_spline_node_t node;
} message_spline_t;

typedef struct {
    uint16_t message_type;
    uint16_t message_id;
    uint16_t message_size;
    union message_data_t {
        track_point_t track_point_data;
        message_spline_t spline_data;
        TYPE_VECTOR(usb_setup_coordinate_t) setup_data;
        struct {
            uint16_t point_id;
        } track_point_acc_data;
    } message_data;
} message_t;

typedef std::shared_ptr<AxisRange> AxisRangePtr;
DECLARE_VECTOR(AxisRangePtr)

#define GENERAL_MESSAGE_HEADER_SIZE() 6

size_t message_spline_size();
size_t message_track_point_size();
size_t message_setup_size();
size_t message_start_size();

#define USB_MESSAGE_SPLINE_TOO_LARGE 0x01
#define USB_MESSAGE_OK 0x00

#endif // USBMESSAGETYPES_H

