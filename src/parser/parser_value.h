#ifndef PARSER_VALUE_H
#define PARSER_VALUE_H

#include "parserspline.h"

typedef enum {
  value_types_number = 0,
  value_types_spline = 1,
} e_value_types;


class Value {
public:
  Value(double number);
  Value(Spline *spline);
  Value(const Value &value);
  double get_number();
  Spline* get_spline();
  e_value_types getType();

private:
  double mNumber;
  Spline *mSpline;
  e_value_types mType;
};

#endif // PARSER_VALUE_H
