#include "abstracttrack.h"
#include "stdio.h"
#include "string.h"


AbstractTrack::AbstractTrack(lines_t *lines, char* projection,
                             TYPE_VECTOR(double) maxVelocity)
    : maxVelocity(maxVelocity) {
    this->lines = lines;
    this->projection = new char[strlen (projection)];
    strcpy (this->projection, projection);
    totalTimeSeconds = calculateAllWorkTime();
}

AbstractTrack::~AbstractTrack() {
    delete[] this->projection;
}

double AbstractTrack::getTotalTimeSeconds() const {
    return totalTimeSeconds;
}

void getAxisNode(line_t *point,
                 ValuePtr &outVariable,
                 char variableName) {
    char varChars[2] = {variableName, '\0'};
    line_t::iterator axisPoint = point->find(std::string(varChars));
    if (axisPoint != point->end()) {
        outVariable.reset (new Value(axisPoint->second));
    }
}

double get_first_number_from_parser_value(Value value) {
    if (value.getType () == value_types_number){
        return value.get_number ();
    } else {
        return (*(value.get_spline ()->get_nodes ().begin ()))->second;
    }
}

double get_last_number_from_parser_value(Value value) {
    if (value.getType () == value_types_number){
        return value.get_number ();
    } else {
        return (*(value.get_spline ()->get_nodes ().rend ()))->second;
    }
}

double AbstractTrack::calculateAllWorkTime() {
    double totalTimeSeconds = 0.0;
    TYPE_VECTOR(ValuePtr) currentCoordinate;
    ValuePtr velocityFactor(new Value(1.0));

    TYPE_VECTOR(double) previousCoordinate;

    trackSegments.clear ();

    for(lines_t::iterator point_it = lines->begin();
        point_it != lines->end ();
        point_it++) {

        line_t *point = *point_it;
        ValuePtr *currentCoordinatePtr = &currentCoordinate.x;

        for (char *coordinate = this->projection;
             *coordinate != '\0';
             coordinate++) {
            getAxisNode(point, *currentCoordinatePtr, *coordinate);
            currentCoordinatePtr++;
        }
        getAxisNode(point, velocityFactor, SPEED_FACTOR_CHAR);


        if (point_it == lines->begin()) {
            currentCoordinatePtr = &currentCoordinate.x;
            double *previousCoordinatePtr = &previousCoordinate.x;

            for (size_t i = 0; i != 4; i++) {
                *previousCoordinatePtr = get_first_number_from_parser_value(
                            *currentCoordinatePtr->get ());
                currentCoordinatePtr++;
                previousCoordinatePtr++;
            }
//            if (currentX.getType () == value_types_number &&
//                    currentY.getType () == value_types_number &&
//                    currentZ.getType () == value_types_number) {
//                continue;
//            }
        }

        TrackSegment4D *currentSegment =
                new TrackSegment4D(
                    previousCoordinate,
                    currentCoordinate,
                    maxVelocity,
                    velocityFactor.get ()->get_number (),
                    totalTimeSeconds);
        trackSegments.push_back(currentSegment);
        totalTimeSeconds += currentSegment->getDeltaTimeSeconds();

        double *previousCoordinatePtr = &previousCoordinate.x;
        currentCoordinatePtr = &currentCoordinate.x;
        for (size_t i = 0; i != 4; i++) {
            *previousCoordinatePtr = get_last_number_from_parser_value(*currentCoordinatePtr->get ());
            currentCoordinatePtr++;
            previousCoordinatePtr++;
        }
    }

    return totalTimeSeconds;
}
