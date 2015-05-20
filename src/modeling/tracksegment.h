#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include <vector>
#include "parser/parser_value.hpp"

#include "interpolation/gsl_spline.h"
//#include "gsl/gsl_statistics_double.h"

class TrackSegment {

public:
    TrackSegment(double maxVelocity,
                 double velocityFactor,
                 double previousPoint,
                 Value nextValue,
                 double previousTimeSeconds);

    void createGSLSpline(gsl_spline **gslSpline);
    void deleteGSLSpline(gsl_spline *gslSpline);
    double getVelocity() const;
    double getDeltaTimeSeconds() const;

    void multiplyVilocityFactors(double velocityFactor);

private:
    double velocity;
    double maxVelocity;

    double previousPoint;

    Value nextValue;

    double velocityFactor;
    double previousTimeSeconds;

    double deltaTimeSeconds;

    std::vector<double> timePointsSeconds;

    void calculateTimeAndVelocity();
    void createLinearGSLSpline(gsl_spline **gslSpline);
    void createCubicGSLSpline (gsl_spline **gslSpline);

};

#endif // TRACKSEGMENT_H
