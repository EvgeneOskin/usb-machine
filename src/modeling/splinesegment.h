#ifndef SPLINESEGMENT_H
#define SPLINESEGMENT_H

#include "string.h"
#include "interpolation/gsl_spline.h"

#define ZERO_FIND_ACCURACY 1e-7
#define ZERO_FIND_MAX_ITER 100


class SplineSegment {
public:
    SplineSegment(double x[], gsl_spline *spline, size_t size, size_t startIndex);
    ~SplineSegment();

    double getTimeSeconds() const;
    double getMaxVelocity() const;

private:
    double *xPoints;
    gsl_spline *spline;
    size_t size;
    size_t startIndex;
    double timeSeconds;
    double maxVelocity;

    void calculateTimeSeconds();
    void calculateMaxVelocity();

    double startTimeSeconds();
    double endTimeSeconds();
};

#endif // SPLINESEGMENT_H
