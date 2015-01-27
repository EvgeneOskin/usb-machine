#ifndef TRACK_H
#define TRACK_H

#include "qwt3d_parametricsurface.h"
#include "parser/parsertypes.hpp"
#include <QString>
#include "tracksegment3d.h"

#define SPEED_FACTOR_NAME "p"

class Track : public Qwt3D::ParametricSurface {

//    Q_OBJECT

public:
    Track(lines_t *lines, QString projection ,Qwt3D::SurfacePlot& pw);
    ~Track();

    Qwt3D::Triple operator()(double u, double /*v*/);
    void setProjection(QString projection);

    double getTotalTimeSeconds() const;

    std::string getXName();
    std::string getYName();
    std::string getZName();

private:
    double x, y, z;
    double velocityX, velocityY, velocityZ;

    double maxVelocityX, maxVelocityY, maxVelocityZ;
    double totalTimeSeconds;


    lines_t *line;
    std::string xName;
    std::string yName;
    std::string zName;
    std::vector<TrackSegment3D*> trackSegments;

    void getAxisNode(line_t *point,
                     Value *outVariable,
                     std::string &variableName);
    double calculateAllWorkTime();

signals:

public slots:

};

#endif // TRACK_H
