#include "track.h"
#include <iostream>
#include <iomanip>
#include "gsl/gsl_spline.h"
#include "gsl/gsl_statistics_double.h"

Track::Track(lines_t* lines, QString projection, Qwt3D::SurfacePlot& pw)
    : Qwt3D::ParametricSurface(pw), x(0), y(0), z(0){
    this->line = lines;
    setProjection(projection);
}

double Track::interpolate(double x, Spline *spline) {
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    const gsl_interp_type *type = gsl_interp_cspline;
    spline_nodes_t nodes = spline->get_nodes();
    size_t size = nodes.size();
    gsl_spline * gslSpline = gsl_spline_alloc (type, size);
    double xa[size], ya[size];
    spline_nodes_t::iterator it = nodes.begin ();
    for (size_t i = 0; i < size; ++i) {
        xa[i] = (*it)->first;
        ya[i] = (*it)->second;
        it++;
    }
    gsl_spline_init(gslSpline, xa, ya, size);
    double maxX = 0.0;
    double minX = 0.0;
    gsl_stats_minmax (&minX, &maxX, xa, 1, size);

    double rescaledX = x*(maxX - minX)/100.0 + minX;
    double result = gsl_spline_eval (gslSpline, rescaledX, acc);
    gsl_spline_free (gslSpline);
    gsl_interp_accel_free (acc);
    return result;
}

void Track::getAxisNode(line_t *point, double afterZero,
                        double *outVariable,
                        std::string &variableName) {
    line_t::iterator axisPoint = point->find(variableName);
    if (axisPoint != point->end()) {
        Value axisValue = axisPoint->second;
        if (axisValue.getType() == value_types_number) {
            *outVariable = axisValue.get_number();
        } else if (axisValue.getType() == value_types_spline) {
            *outVariable = interpolate(afterZero, axisValue.get_spline());
        }
    }
}

Qwt3D::Triple Track::operator() (double u, double /*v*/) {
    size_t counter = 0;
    line_t *point;
    foreach(line_t *i, *line) {
        if (counter == (size_t) fabs(round(u)) || counter == line->size() - 1) {
            point = i;
            break;
        }
        counter++;
    }
    double afterZero = u - (double)counter;
    getAxisNode(point, afterZero, &x, x1);
    getAxisNode(point, afterZero, &y, y1);
    getAxisNode(point, afterZero, &z, z1);

    return Qwt3D::Triple(x, y, z);
}


void Track::setProjection(QString projection) {
    std::string std_proj = projection.toStdString();
    x1 = std_proj.substr(0, 1);
    y1 = std_proj.substr(1, 1);
    z1 = std_proj.substr(2, 1);
}

std::string Track::getX1() {
    return x1;
}

std::string Track::getY1() {
    return y1;
}

std::string Track::getZ1() {
    return z1;
}
