#ifndef TRACKSEGMENT3D_H
#define TRACKSEGMENT3D_H

#include "tracksegment.h"
#include "parser/parser_value.hpp"
#include "interpolation/gsl_spline.h"

class TrackSegment3D {

public:
    TrackSegment3D(
            double previousX, double previousY, double previousZ,
            Value nextX, Value nextY, Value nextZ,
            double maxVelocityX, double maxVelocityY, double maxVelocityZ,
            double velocityFactor, double previousTimeSeconds);
    ~TrackSegment3D();

    bool isTimeInSegment(double timeSeconds) const;
    double getDeltaTimeSeconds() const;

    gsl_spline* getXGSLSpline() const;
    gsl_spline* getYGSLSpline() const;
    gsl_spline* getZGSLSpline() const;

private:
    TrackSegment *xSegment;
    gsl_spline *xGSLSpline;

    TrackSegment *ySegment;
    gsl_spline *yGSLSpline;

    TrackSegment *zSegment;
    gsl_spline *zGSLSpline;

    double startTimeSeconds;
    double endTimeSeconds;
    double maxDeltaTimeSeconds;

    void correctSegmentVelocity();
    void initMaxDeltaTimeSeconds();
};

#endif // TRACKSEGMENT3D_H
