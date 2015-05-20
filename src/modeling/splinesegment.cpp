#include "splinesegment.h"
#include <cmath>

#include <vector/gsl_vector.h>
#include <interpolation/gsl_spline.h>
#include <gsl_nan.h>

#define GSL_MAX(a,b)  (a > b ? a : b)

SplineSegment::SplineSegment(double x[], gsl_spline *spline,
                             size_t size, size_t startIndex) :
    spline(spline), size(size),
    startIndex(startIndex), timeSeconds(0.0),
    maxVelocity(0.0) {

    this->xPoints = x;

    if (startIndex >= size) {
        throw "Error bad size";
    }

    calculateMaxVelocity ();
    calculateTimeSeconds ();
}

SplineSegment::~SplineSegment() {
}

double SplineSegment::getTimeSeconds() const {
    return timeSeconds;
}

double SplineSegment::getMaxVelocity () const {
    return maxVelocity;
}

void SplineSegment::calculateMaxVelocity() {
    gsl_interp_accel *acc;
    size_t minSplineSize = gsl_spline_min_size (spline);

    if (size < minSplineSize) {
        return;
    }

    acc = gsl_interp_accel_alloc ();

    double x_low = startTimeSeconds(), x_high = endTimeSeconds();
    double deriv2_y_low = gsl_spline_eval_deriv2(spline, x_low, acc);
    double deriv2_y_high = gsl_spline_eval_deriv2(spline, x_high, acc);

    // FIXME Hardcoded find zero formula!!! for linear function,
    // because second derivation of cubic function (spline function between nodes)
    // is linear function
    double founded_zero = -deriv2_y_low/(deriv2_y_high - deriv2_y_low)*(x_high - x_low) + x_low;

    if (founded_zero != GSL_NAN && x_low < founded_zero && founded_zero < x_high) {
        maxVelocity = fabs(gsl_spline_eval_deriv(spline, founded_zero, acc));
    } else {
        maxVelocity = fabs(gsl_spline_eval_deriv(spline, (x_low + x_high)/2.0, acc));
    }

    double dy_low = fabs(gsl_spline_eval_deriv(spline, x_low, acc));
    double dy_high = fabs(gsl_spline_eval_deriv(spline, x_high, acc));

    maxVelocity = GSL_MAX(GSL_MAX(maxVelocity, dy_low), dy_high);

    gsl_interp_accel_free(acc);
}

void SplineSegment::calculateTimeSeconds () {
    timeSeconds = endTimeSeconds() - startTimeSeconds();
}

double SplineSegment::startTimeSeconds(){
    return xPoints[startIndex];
}

double SplineSegment::endTimeSeconds(){
    return xPoints[startIndex + 1];
}
