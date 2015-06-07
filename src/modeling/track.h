#ifndef TRACK_H
#define TRACK_H

#include "qwt3d_parametricsurface.h"
#include "parser/parsertypes.h"
#include <QString>
#include "abstracttrack.h"

#define SPEED_FACTOR_NAME "p"

class Track : public Qwt3D::ParametricSurface, public AbstractTrack {

//    Q_OBJECT

public:
    Track(lines_t *lines, QString projection, Qwt3D::SurfacePlot& pw);
    ~Track();

    Qwt3D::Triple operator()(double u, double /*v*/);
    void setProjection(QString projection);

    std::string getXName();
    std::string getYName();
    std::string getZName();

private:
    double x, y, z;

    std::string xName;
    std::string yName;
    std::string zName;


signals:

public slots:

};

#endif // TRACK_H
