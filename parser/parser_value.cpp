#include "value.h"

Value::Value(double number) : mNumber(number), mSpline(), mType(value_types_number) {}
Value::Value(Spline spline) : mNumber(0), mSpline(spline), mType(value_types_spline) {}
