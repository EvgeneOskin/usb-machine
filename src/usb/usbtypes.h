#ifndef USBTYPES_H
#define USBTYPES_H

#include "axisrange.h"

#include "parser/parser_value.hpp"

typedef std::map< std::string, Value >* frame_t;
typedef std::list< std::map< std::string, Value > * > frames_t;

typedef std::map<std::string, AxisRange*> axis_ranges_t;
typedef std::pair<std::string, AxisRange*> axis_range_pair_t;

#endif // USBTYPES_H

