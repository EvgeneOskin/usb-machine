#include "track.h"
#include <iostream>
#include <iomanip>
#include "gsl/gsl_spline.h"

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

//double Track::interpolate(double x, Spline *spline) {
//    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
//    const gsl_interp_type *type = gsl_interp_cspline;
//    spline_nodes_t nodes = spline->get_nodes();
//    size_t size = nodes.size();
//    gsl_spline * gslSpline = gsl_spline_alloc (type, size);
//    double xa[size], ya[size];
//    spline_nodes_t::iterator it = nodes.begin ();
//    for (size_t i = 0; i < size; ++i) {
//        xa[i] = (*it)->first;
//        ya[i] = (*it)->second;
//        it++;
//    }
//    gsl_spline_init(gslSpline, xa, ya, size);
//    double maxX = 0.0;
//    double minX = 0.0;
//    gsl_stats_minmax (&minX, &maxX, xa, 1, size);

//    double rescaledX = x*(maxX - minX)/100.0 + minX;
//    double result = gsl_spline_eval (gslSpline, rescaledX, acc);
//    gsl_spline_free (gslSpline);
//    gsl_interp_accel_free (acc);
//    return result;
//}

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

            x = gsl_spline_eval (xSpline, u, acc);
            y = gsl_spline_eval (ySpline, u, acc);
            z = gsl_spline_eval (zSpline, u, acc);

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

    foreach(line_t *point, *line) {
        getAxisNode(point, &currentX, xName);
        getAxisNode(point, &currentY, yName);
        getAxisNode(point, &currentZ, zName);
        getAxisNode(point, &velocityFactor, velocity_factor_string);


        if (totalTimeSeconds == 0.0) {
            if (currentX.getType () == value_types_number){
                previousX = currentX.get_number ();
            } else {
                previousX = (*(currentX.get_spline ()->get_nodes ().begin ()))->second;
            }
            if (currentY.getType () == value_types_number){
                previousY = currentY.get_number();
            } else {
                previousY = (*(currentY.get_spline ()->get_nodes ().begin ()))->second;
            }
            if (currentZ.getType () == value_types_number){
                previousZ = currentZ.get_number ();
            } else {
                previousZ = (*(currentZ.get_spline ()->get_nodes ().begin ()))->second;
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
