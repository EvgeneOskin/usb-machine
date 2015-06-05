#ifndef MODELINGVECTORTYPES_H
#define MODELINGVECTORTYPES_H

#include "parser/parsertypes.h"
#include "tracksegment.h"
#include "interpolation/gsl_spline.h"
#include <memory>

typedef std::shared_ptr<Value> ValuePtr;
typedef gsl_spline* gsl_spline_ptr;

#define TYPE_VECTOR(type) vector_##type
#define NAME_GET_VECTOR_COORDINATE(type) get_vector_coordinate_##type

#define DECLARE_VECTOR(type) \
typedef struct { \
    type x; type y; type z; type f; \
} TYPE_VECTOR(type); \
type NAME_GET_VECTOR_COORDINATE(type)(TYPE_VECTOR(type) *vector, char varChar);

#define DECLARE_GET_VECTOR_COORDINATE(type) \
type NAME_GET_VECTOR_COORDINATE(type)(TYPE_VECTOR(type) *vector, char varChar) { \
    switch(varChar) { \
        case 'x': return vector->x; \
        case 'y': return vector->y; \
        case 'z': return vector->z; \
        case 'f': return vector->f; \
        default: \
            throw std::runtime_error("You take not valid coordinate."); \
    } \
}

DECLARE_VECTOR(double)
DECLARE_VECTOR(ValuePtr)
DECLARE_VECTOR(gsl_spline_ptr)

#endif // MODELINGVECTORTYPES_H

