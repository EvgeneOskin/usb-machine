#ifndef TRACK_H
#define TRACK_H

#include "qwt3d_parametricsurface.h"
#include "parsertypes.hpp"
#include <QString>

class Track : public Qwt3D::ParametricSurface {

public:
    Track(lines_t *lines, QString projection ,Qwt3D::SurfacePlot& pw);

    Qwt3D::Triple operator()(double u, double /*v*/);
    void setProjection(QString projection);

    std::string getX1();
    std::string getY1();
    std::string getZ1();

private:
    double x, y, z;
    lines_t *line;
    std::string x1;
    std::string y1;
    std::string z1;
    double interpolate(double x, Spline *spline);
    void getAxisNode(line_t *point, double afterZero,
                     double *outVariable,
                     std::string &variableName);
signals:

public slots:

};

#endif // TRACK_H
