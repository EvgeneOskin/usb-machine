#include "parser_value.hpp"

Value::Value(double number) : mNumber(number), mSpline(NULL), mType(value_types_number) {}
Value::Value(Spline *spline) : mNumber(0), mSpline(spline), mType(value_types_spline) {}

double Value::get_number() {
  if (mType == value_types_number) {
    return mNumber;
  } else {
    // TODO need to handle error here.
    return 0;
  }
}

Spline* Value::get_spline() {
  if (mType == value_types_spline) {
    return mSpline;
  } else {
    // TODO need to handle error here.
    return NULL;
  }
}

e_value_types Value::getType() {
  return mType;
}
