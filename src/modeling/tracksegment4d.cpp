#include "tracksegment4d.h"

#include "gsl/gsl_math.h"

TrackSegment4D::TrackSegment4D(
        TYPE_VECTOR(double) previousCoordinate,
        TYPE_VECTOR(ValuePtr) nextCoordinate,
        TYPE_VECTOR(double) maxVelocity,
        double velocityFactor, double previousTimeSeconds) :
    startTimeSeconds(previousTimeSeconds) {

    double *previousCoordinatePtr = &previousCoordinate.x;
    double *maxVelocityPtr = &maxVelocity.x;
    ValuePtr *nextCoordinatePtr = &nextCoordinate.x;
    TrackSegmentPtr *segmentsPtrPtr = &segments.x;

    for (int i = 0; i < 4; i++) {
        *segmentsPtrPtr = new TrackSegment (
                    *maxVelocityPtr, velocityFactor,
                    *previousCoordinatePtr, *nextCoordinatePtr->get (),
                    previousTimeSeconds);
        previousCoordinatePtr++;
        maxVelocityPtr++;
        nextCoordinatePtr++;
        segmentsPtrPtr++;
    }

    initMaxDeltaTimeSeconds();

    correctSegmentVelocity();

    segmentsPtrPtr = &segments.x;
    gsl_spline_ptr *GSLSplinePtrPtr = &GSLSplines.x;
    for (int i = 0; i < 4; i++) {
        (*segmentsPtrPtr)->createGSLSpline(GSLSplinePtrPtr);
        GSLSplinePtrPtr++;
        segmentsPtrPtr++;
    }
}

TrackSegment4D::~TrackSegment4D() {
    TrackSegmentPtr *segmentsPtrPtr = &segments.x;
    gsl_spline_ptr *GSLSplinePtrPtr = &GSLSplines.x;
    for (int i = 0; i < 4; i++) {
        (*segmentsPtrPtr)->deleteGSLSpline(*GSLSplinePtrPtr);
        GSLSplinePtrPtr++;
        delete segmentsPtrPtr;
    }
}

double TrackSegment4D::getDeltaTimeSeconds() const {
    return maxDeltaTimeSeconds;
}

bool TrackSegment4D::isTimeInSegment(double timeSeconds) const {
    return startTimeSeconds <= timeSeconds && timeSeconds < startTimeSeconds + maxDeltaTimeSeconds;
}

void TrackSegment4D::initMaxDeltaTimeSeconds() {
    double tempDeltaTimeSeconds;
    TrackSegmentPtr *segmentsPtrPtr = &segments.x;
    for (int i = 0; i < 4; i++) {
        tempDeltaTimeSeconds = (*segmentsPtrPtr)->getDeltaTimeSeconds ();
        segmentsPtrPtr++;
        maxDeltaTimeSeconds = GSL_MAX(maxDeltaTimeSeconds, tempDeltaTimeSeconds);
    }
}

void TrackSegment4D::correctSegmentVelocity() {
    double deltaTimeSeconds;
    TrackSegmentPtr *segmentsPtrPtr = &segments.x;
    for (int i = 0; i < 4; i++) {
        deltaTimeSeconds = (*segmentsPtrPtr)->getDeltaTimeSeconds ();
        (*segmentsPtrPtr)->multiplyVilocityFactors (deltaTimeSeconds/maxDeltaTimeSeconds);
        segmentsPtrPtr++;
    }
}

void TrackSegment4D::getGSLSplines(TYPE_VECTOR(gsl_spline_ptr) *result) const {
    result->x = GSLSplines.x;
    result->y = GSLSplines.y;
    result->z = GSLSplines.z;
    result->f = GSLSplines.f;
}
