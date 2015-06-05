#ifndef TRACKSEGMENT3D_H
#define TRACKSEGMENT3D_H

#include "tracksegment.h"
#include "modelingvectortypes.h"


typedef TrackSegment* TrackSegmentPtr;
DECLARE_VECTOR(TrackSegmentPtr)

class TrackSegment4D {

public:
    TrackSegment4D(
            TYPE_VECTOR(double) previousCoordinate,
            TYPE_VECTOR(ValuePtr) nextCoordinate,
            TYPE_VECTOR(double) maxVelocity,
            double velocityFactor, double previousTimeSeconds);
    ~TrackSegment4D();

    bool isTimeInSegment(double timeSeconds) const;
    double getDeltaTimeSeconds() const;

    void getGSLSplines(TYPE_VECTOR(gsl_spline_ptr) *result) const;

private:

    TYPE_VECTOR(TrackSegmentPtr) segments;
    TYPE_VECTOR(gsl_spline_ptr) GSLSplines;

    double startTimeSeconds;
    double endTimeSeconds;
    double maxDeltaTimeSeconds;

    void correctSegmentVelocity();
    void initMaxDeltaTimeSeconds();
};

#endif // TRACKSEGMENT3D_H
