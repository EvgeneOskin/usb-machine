#ifndef PARSERTYPES_H
#define PARSERTYPES_H

#include <list>
#include <map>
#include <string>
#include "parser_value.hpp"


typedef std::map< std::string, Value > line_t;
typedef std::list< std::map< std::string, Value > * > lines_t;
typedef std::pair< std::string, Value > variable;

#endif // PARSERTYPES_H
