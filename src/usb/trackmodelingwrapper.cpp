#include "trackmodelingwrapper.h"
#include <cstring>

double get_last_time_value(gsl_spline_ptr spline) {
    return spline->x[spline->size - 1];
}

double get_first_time_value(gsl_spline_ptr spline) {
    return spline->x[0];
}

void convert_gsl_spline_to_usb_spline(
        AxisRangePtr *coordinateRange,
        gsl_spline_ptr gslSpline,
        usb_spline_nodes_t *usb_spline,
        uint8_t *errorCode) {
    AxisRange timeRange(
                get_first_time_value (gslSpline),
                get_last_time_value (gslSpline)
                );
    if (gslSpline->size >= MAX_SPLINE_NODE_COUNT) {
        *errorCode = USB_MESSAGE_SPLINE_TOO_LARGE;
        return;
    }

    for (size_t i = 0; i < gslSpline->size; i++) {
        message_spline_node_t node = {
                    timeRange.setPositionInRange(gslSpline->x[i]),
                    coordinateRange->get()->setPositionInRange(gslSpline->y[i])
                    };
        usb_spline->push_back (node);
    }
}

TrackModelingWrapper::TrackModelingWrapper(
        lines_t *lines,
        TYPE_VECTOR(double) maxVelocity,
        TYPE_VECTOR(uint16_t) coordinateScale,
        TYPE_VECTOR(uint16_t) velocityScale,
        TYPE_VECTOR(AxisRangePtr) ranges)
    : AbstractTrack(lines, "xyzf", maxVelocity) {

    errorCode = USB_MESSAGE_OK;

    memcpy(&this->velocityScale, &velocityScale, sizeof(TYPE_VECTOR(uint16_t)));
    memcpy(&this->coordinateScale, &coordinateScale, sizeof(TYPE_VECTOR(uint16_t)));

    for (std::vector<TrackSegment4D*>::iterator it = trackSegments.begin (); it != trackSegments.end (); it++) {
        TYPE_VECTOR(gsl_spline_ptr) pointSplines;
        (*it)->getGSLSplines(&pointSplines);

        track_point_t track_point_data;

        gsl_spline_ptr *gsl_spline_ptr_ptr = &pointSplines.x;
        usb_point_coordinate_t *coordinate = &track_point_data.coordinates.x;
        AxisRangePtr *coordinateRange = &ranges.x;
        // time of point is last known time
        track_point_data.point_id = get_last_time_value(*gsl_spline_ptr_ptr);

        for (int i = 0; i < 4; i++) {
            if ((*gsl_spline_ptr_ptr)->interp->type == gsl_interp_cspline) {
                coordinate->value = splineIdGenrator.generate ();

                usb_spline_nodes_t usb_spline;
                convert_gsl_spline_to_usb_spline(
                            coordinateRange, *gsl_spline_ptr_ptr,
                            &usb_spline, &errorCode);

                splines.insert (spline_map_node_t(coordinate->value, usb_spline));
                coordinate->type = TRACK_POINT_TYPE_SPLINE;
            } else if ((*gsl_spline_ptr_ptr)->interp->type == gsl_interp_linear){
                coordinate->type = TRACK_POINT_TYPE_VALUE;
                coordinate->value = coordinateRange->get()->setPositionInRange(
                            (*gsl_spline_ptr_ptr)->y[1]
                );
            }
            gsl_spline_ptr_ptr++;
            coordinate++;
            coordinateRange++;
        }
        points.push_back (track_point_data);
    }
}

TrackModelingWrapper::~TrackModelingWrapper() {
}

bool TrackModelingWrapper::hasError() {
    return errorCode != USB_MESSAGE_OK;
}

size_t TrackModelingWrapper::getUsbSplineMessagesCount() {
    size_t packagesCount = 0;
    if (!splines.empty ()) {
        for (spline_map_t::iterator it = splines.begin ();
             it != splines.end ();
             it++) {
            packagesCount += ((usb_spline_nodes_t) it->second).size ();
        }
    }
    return packagesCount;
}

void TrackModelingWrapper::copySplineMessageData(size_t index, message_t *message) {
    if (!splines.empty ()) {
        size_t packagesCount = 0;
        size_t splineSize = 0;
        for (spline_map_t::iterator it = splines.begin ();
             it != splines.end ();
             it++) {
            splineSize = it->second.size ();
            if (packagesCount <= index && index < packagesCount + splineSize) {
                usb_spline_nodes_t::iterator node_it = it->second.begin();
                std::advance(node_it, index - packagesCount);

                message->message_id = messageIdGenerator.generate ();
                message->message_type = MESSAGE_TYPE_SPLINE;
                message->message_size = message_spline_size();
                message->message_data.spline_data.spline_id = std::distance(it, splines.begin ());
                memcpy(&message->message_data.spline_data.node, &(*node_it), sizeof(message_spline_node_t));

                break;
            } else {
                packagesCount += splineSize;
            }
        }
    }
}

size_t TrackModelingWrapper::getUsbPointMessagesCount () {
    return points.size ();
}

void TrackModelingWrapper::copyPointMessageData(size_t index, message_t *message) {
    std::vector <track_point_t> ::iterator it = points.begin ();
    std::advance(it, index);
    message->message_id = messageIdGenerator.generate ();
    message->message_type = MESSAGE_TYPE_TRACK_POINT;
    memcpy(&message->message_data.track_point_data, &(*it), sizeof(track_point_t));
    message->message_size = message_track_point_size ();
}

void TrackModelingWrapper::copySetupMessageData(message_t *message) {
    message->message_id = messageIdGenerator.generate ();
    message->message_type = MESSAGE_TYPE_SETUP;
    message->message_size = message_setup_size();
    uint16_t *coordinateScalePtr = &coordinateScale.x;
    uint16_t *velocityScalePtr = &velocityScale.x;
    usb_setup_coordinate_t *setupDataPtr = &message->message_data.setup_data.x;
    for (int i = 0; i < 4; i++) {
        setupDataPtr->scale = *coordinateScalePtr;
        setupDataPtr->velocity_scale = *velocityScalePtr;
        coordinateScalePtr++;
        velocityScalePtr++;
        setupDataPtr++;
    }
}

void TrackModelingWrapper::copyStartMessageData(message_t *message) {
    message->message_id = messageIdGenerator.generate ();
    message->message_type = MESSAGE_TYPE_START;
    message->message_size = 0;
}
