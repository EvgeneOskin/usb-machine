#include "tracksegment.h"

#include "splinesegment.h"
#include "gsl_math.h"
#include "interpolation/gsl_spline.h"

TrackSegment::TrackSegment(double maxVelocity,
                           double velocityFactor,
                           double previousPoint,
                           Value nextValue,
                           double previousTimeSeconds) :
    maxVelocity(maxVelocity),
    previousPoint(previousPoint),
    nextValue(nextValue),
    velocityFactor(velocityFactor),
    previousTimeSeconds(previousTimeSeconds) {

    calculateTimeAndVelocity();
    multiplyVilocityFactors (maxVelocity/getVelocity());
    calculateTimeAndVelocity();
}

double TrackSegment::getVelocity () const {
    return velocity;
}

double TrackSegment::getDeltaTimeSeconds() const {
    return deltaTimeSeconds;
}


void TrackSegment::createLinearGSLSpline(gsl_spline **gslSpline) {
    const gsl_interp_type *type = gsl_interp_linear;
    size_t size = 2;
    *gslSpline = gsl_spline_alloc (type, size);
    double xa[size];
    double ya[size];
    xa[0] = previousTimeSeconds;
    ya[0] = previousPoint;

    xa[1] = previousTimeSeconds + (nextValue.get_number() - previousPoint)/velocity;
    ya[1] = nextValue.get_number();

    gsl_spline_init(*gslSpline, xa, ya, size);
}

void TrackSegment::createCubicGSLSpline (gsl_spline **gslSpline) {
    const gsl_interp_type *type = gsl_interp_cspline;
    spline_nodes_t nodes = nextValue.get_spline()->get_nodes();
    size_t size = nodes.size();
    *gslSpline = gsl_spline_alloc (type, size);
    double xa[size], ya[size];
    spline_nodes_t::iterator splineIt = nodes.begin ();
    std::vector<double>::iterator timePointsIt = timePointsSeconds.begin ();

    for (size_t i = 0; i < size; ++i) {
        xa[i] = previousTimeSeconds + (*timePointsIt);
        ya[i] = (*splineIt)->second + previousPoint;

        splineIt++;
        timePointsIt++;
    }
    gsl_spline_init(*gslSpline, xa, ya, size);
}

void TrackSegment::createGSLSpline(gsl_spline **gslSpline) {
    if (nextValue.getType () == value_types_number) {
        createLinearGSLSpline (gslSpline);
    } else {
        createCubicGSLSpline (gslSpline);
    }
}

void TrackSegment::deleteGSLSpline(gsl_spline *gslSpline) {
    gsl_spline_free(gslSpline);
}


void TrackSegment::multiplyVilocityFactors(double velocityFactor) {
    this->velocityFactor *= velocityFactor;
    this->velocity *= velocityFactor;
    deltaTimeSeconds /= velocityFactor;

    for (std::vector<double>::iterator it = timePointsSeconds.begin ();
         it != timePointsSeconds.end();
         ++it) {
        *it = (*it)/velocityFactor;
    }
}

void TrackSegment::calculateTimeAndVelocity() {
    double tempDeltaTimeSeconds = 0.0;
    timePointsSeconds.clear ();
    timePointsSeconds.push_back (tempDeltaTimeSeconds);

    if (nextValue.getType () == value_types_number){
        velocity = fabs(velocityFactor/maxVelocity);
        tempDeltaTimeSeconds = fabs(nextValue.get_number ()- previousPoint)/velocity;
        timePointsSeconds.push_back (tempDeltaTimeSeconds);
    } else {
        spline_nodes_t nodes = nextValue.get_spline ()->get_nodes ();
        const gsl_interp_type *type = gsl_interp_cspline;
        size_t size = nodes.size();
        gsl_spline *gslSpline = gsl_spline_alloc (type, size);
        double xa[size], ya[size];
        spline_nodes_t::iterator it = nodes.begin ();
        for (size_t i = 0; i < size; ++i) {
            xa[i] = (*it)->first;
            ya[i] = (*it)->second;
            it++;
        }

        gsl_spline_init (gslSpline, xa, ya, size);
        velocity = 0.0;
        for (size_t i = 0; i < size - 1; ++i) {
            SplineSegment splineSegment(xa, gslSpline, size, i);
            velocity = GSL_MAX(velocity, fabs(splineSegment.getMaxVelocity ()));
            tempDeltaTimeSeconds += splineSegment.getTimeSeconds();
            timePointsSeconds.push_back (tempDeltaTimeSeconds);
        }
    }

    this->deltaTimeSeconds = tempDeltaTimeSeconds ;
}
