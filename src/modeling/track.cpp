#include "track.h"
#include <iostream>
#include <iomanip>
#include "interpolation/gsl_spline.h"


TYPE_VECTOR(double) maxVelocity = {1.0, 1.0, 1.0, 1.0};

Track::Track(lines_t* lines, QString projection, Qwt3D::SurfacePlot& pw)
    : Qwt3D::ParametricSurface(pw),
      AbstractTrack(lines, "xyzf", maxVelocity) {
    setProjection(projection);
}

Track::~Track() {
    for (std::vector<TrackSegment4D*>::iterator it = trackSegments.begin();
         it != trackSegments.end();
         ++it) {
        delete *it;
    }
}


Qwt3D::Triple Track::operator() (double u, double /*v*/) {
    for (std::vector<TrackSegment4D*>::iterator it = trackSegments.begin();
         it != trackSegments.end();
         ++it) {
        if ((*it)->isTimeInSegment(u)) {
            TYPE_VECTOR(gsl_spline_ptr) result;
            (*it)->getGSLSplines(&result);

            gsl_spline_ptr xSpline = NAME_GET_VECTOR_COORDINATE(gsl_spline_ptr)(
                        &result, xName[0]);
            gsl_spline_ptr ySpline = NAME_GET_VECTOR_COORDINATE(gsl_spline_ptr)(
                        &result, yName[0]);
            gsl_spline_ptr zSpline = NAME_GET_VECTOR_COORDINATE(gsl_spline_ptr)(
                        &result, zName[0]);

            x = gsl_spline_eval (xSpline, u, NULL);
            y = gsl_spline_eval (ySpline, u, NULL);
            z = gsl_spline_eval (zSpline, u, NULL);

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
