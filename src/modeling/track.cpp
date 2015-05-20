#include "track.h"
#include <iostream>
#include <iomanip>
#include "interpolation/gsl_spline.h"

Track::Track(lines_t* lines, QString projection, Qwt3D::SurfacePlot& pw)
    : Qwt3D::ParametricSurface(pw), x(0), y(0), z(0),
      maxVelocityX(1.0), maxVelocityY(1.0), maxVelocityZ(1.0) {
    this->line = lines;
    setProjection(projection);
    totalTimeSeconds = calculateAllWorkTime();
}

Track::~Track() {
    for (std::vector<TrackSegment3D*>::iterator it = trackSegments.begin();
         it != trackSegments.end();
         ++it) {
        delete *it;
    }
}

double Track::getTotalTimeSeconds() const {
    return totalTimeSeconds;
}

void Track::getAxisNode(line_t *point,
                        Value *outVariable,
                        std::string &variableName) {
    line_t::iterator axisPoint = point->find(variableName);
    if (axisPoint != point->end()) {
        *outVariable = axisPoint->second;
    }
}

Qwt3D::Triple Track::operator() (double u, double /*v*/) {
    for (std::vector<TrackSegment3D*>::iterator it = trackSegments.begin();
         it != trackSegments.end();
         ++it) {
        if ((*it)->isTimeInSegment(u)) {
            gsl_interp_accel *acc = gsl_interp_accel_alloc ();

            const gsl_spline *xSpline = (*it)->getXGSLSpline();
            const gsl_spline *ySpline = (*it)->getYGSLSpline();
            const gsl_spline *zSpline = (*it)->getZGSLSpline();

            y = gsl_spline_eval (ySpline, u, acc);
            z = gsl_spline_eval (zSpline, u, acc);
            x = gsl_spline_eval (xSpline, u, acc);

            gsl_interp_accel_free (acc);
            return Qwt3D::Triple(x, y, z);
        }
    }
    return Qwt3D::Triple(x, y, z);
}


void Track::setProjection(QString projection) {
    std::string std_proj = projection.toStdString();
    xName = std_proj.substr(0, 1);
    yName = std_proj.substr(1, 1);
    zName = std_proj.substr(2, 1);
}

std::string Track::getXName() {
    return xName;
}

std::string Track::getYName() {
    return yName;
}

std::string Track::getZName() {
    return zName;
}

double get_number_from_parser_value(Value value) {
    if (value.getType () == value_types_number){
        return value.get_number ();
    } else {
        return (*(value.get_spline ()->get_nodes ().begin ()))->second;
    }
}

double Track::calculateAllWorkTime() {
    double totalTimeSeconds = 0.0;
    Value currentX(0.0);
    Value currentY(0.0);
    Value currentZ(0.0);
    Value velocityFactor(1.0);

    std::string velocity_factor_string(SPEED_FACTOR_NAME);

    double previousX = 0.0;
    double previousY = 0.0;
    double previousZ = 0.0;

    trackSegments.clear ();

    for(lines_t::iterator point_it = line->begin();
        point_it != line->end ();
        point_it++) {

        line_t *point = *point_it;
        getAxisNode(point, &currentX, xName);
        getAxisNode(point, &currentY, yName);
        getAxisNode(point, &currentZ, zName);
        getAxisNode(point, &velocityFactor, velocity_factor_string);


        if (point_it == line->begin()) {
            previousX = get_number_from_parser_value(currentX);
            previousY = get_number_from_parser_value(currentY);
            previousZ = get_number_from_parser_value(currentZ);
            if (currentX.getType () == value_types_number &&
                    currentY.getType () == value_types_number &&
                    currentZ.getType () == value_types_number) {
                continue;
            }
        }

        TrackSegment3D *currentSegment =
                new TrackSegment3D(
                    previousX, previousY, previousZ,
                    currentX, currentY, currentZ,
                    maxVelocityX, maxVelocityY, maxVelocityZ,
                    velocityFactor.get_number (),
                    totalTimeSeconds);
        trackSegments.push_back(currentSegment);
        totalTimeSeconds += currentSegment->getDeltaTimeSeconds();
    }

    return totalTimeSeconds;
}
