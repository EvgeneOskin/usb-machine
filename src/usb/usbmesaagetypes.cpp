#include "usbmesaagetypes.h"

DECLARE_GET_VECTOR_COORDINATE(usb_point_coordinate_t)
DECLARE_GET_VECTOR_COORDINATE(usb_setup_coordinate_t)
DECLARE_GET_VECTOR_COORDINATE(AxisRangePtr)

size_t message_spline_size() {
    return sizeof(message_spline_t);
}

size_t message_track_point_size() {
    return sizeof(track_point_t);
}

size_t message_setup_size() {
    return sizeof(TYPE_VECTOR(usb_setup_coordinate_t));
}

size_t message_start_size() {
    return 0;
}
