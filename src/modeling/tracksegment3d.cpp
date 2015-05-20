#include "tracksegment3d.h"

#include "gsl_math.h"

TrackSegment3D::TrackSegment3D(
        double previousX, double previousY, double previousZ,
        Value nextX, Value nextY, Value nextZ,
        double maxVelocityX, double maxVelocityY, double maxVelocityZ,
        double velocityFactor, double previousTimeSeconds) :
    startTimeSeconds(previousTimeSeconds) {

    xSegment = new TrackSegment (
                maxVelocityX, velocityFactor,
                previousX, nextX,
                previousTimeSeconds);
    ySegment = new TrackSegment (
                maxVelocityY, velocityFactor,
                previousY, nextY,
                previousTimeSeconds);
    zSegment = new TrackSegment (
                maxVelocityZ, velocityFactor,
                previousZ, nextZ,
                previousTimeSeconds);

    initMaxDeltaTimeSeconds();

    correctSegmentVelocity();

    xSegment->createGSLSpline (&xGSLSpline);
    ySegment->createGSLSpline (&yGSLSpline);
    zSegment->createGSLSpline (&zGSLSpline);
}

TrackSegment3D::~TrackSegment3D() {
    xSegment->deleteGSLSpline (xGSLSpline);
    ySegment->deleteGSLSpline (yGSLSpline);
    zSegment->deleteGSLSpline (zGSLSpline);

    delete xSegment;
    delete ySegment;
    delete zSegment;
}

double TrackSegment3D::getDeltaTimeSeconds() const {
    return maxDeltaTimeSeconds;
}

bool TrackSegment3D::isTimeInSegment(double timeSeconds) const {
    return startTimeSeconds < timeSeconds && timeSeconds < startTimeSeconds + maxDeltaTimeSeconds;
}

void TrackSegment3D::initMaxDeltaTimeSeconds() {
    double xDeltaTimeSeconds = xSegment->getDeltaTimeSeconds ();
    double yDeltaTimeSeconds = ySegment->getDeltaTimeSeconds ();
    double zDeltaTimeSeconds = zSegment->getDeltaTimeSeconds ();

    maxDeltaTimeSeconds = GSL_MAX(GSL_MAX(xDeltaTimeSeconds, yDeltaTimeSeconds), zDeltaTimeSeconds);
}

void TrackSegment3D::correctSegmentVelocity() {
    double xDeltaTimeSeconds = xSegment->getDeltaTimeSeconds ();
    double yDeltaTimeSeconds = ySegment->getDeltaTimeSeconds ();
    double zDeltaTimeSeconds = zSegment->getDeltaTimeSeconds ();

    xSegment->multiplyVilocityFactors (xDeltaTimeSeconds/maxDeltaTimeSeconds);
    ySegment->multiplyVilocityFactors (yDeltaTimeSeconds/maxDeltaTimeSeconds);
    zSegment->multiplyVilocityFactors (zDeltaTimeSeconds/maxDeltaTimeSeconds);
}

gsl_spline* TrackSegment3D::getXGSLSpline() const {
    return xGSLSpline;
}

gsl_spline* TrackSegment3D::getYGSLSpline() const {
    return yGSLSpline;
}

gsl_spline* TrackSegment3D::getZGSLSpline() const {
    return zGSLSpline;
}
