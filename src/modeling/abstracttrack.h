#ifndef ABSTRACTTRACK_H
#define ABSTRACTTRACK_H

#include "modelingvectortypes.h"
#include "tracksegment4d.h"

#define SPEED_FACTOR_CHAR 'p'

class AbstractTrack
{
public:
    AbstractTrack(
            lines_t *lines, char* projection,
            TYPE_VECTOR(double) maxVelocity);
    ~AbstractTrack();

    double getTotalTimeSeconds() const;

protected:
    TYPE_VECTOR(double) maxVelocity;
    TYPE_VECTOR(double) currentCoordinate;
    double totalTimeSeconds;


    lines_t *lines;
    char* projection;
    std::vector<TrackSegment4D*> trackSegments;

    double calculateAllWorkTime();
};

#endif // ABSTRACTTRACK_H
