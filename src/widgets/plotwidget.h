#ifndef JENIA_H
#define JENIA_H

#include "qwt3d_surfaceplot.h"
#include "qwt3d_parametricsurface.h"
#include "parser/parsertypes.h"

class PlotWidget : public Qwt3D::SurfacePlot {

    Q_OBJECT
public:
    PlotWidget();
    void updateLine();
    void updateProjection(std::string x1, std::string y1, std::string z1);
};

#endif // JENIA_H
