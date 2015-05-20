#ifndef PARSERTYPES_H
#define PARSERTYPES_H

#include <list>
#include <map>
#include <string>
#include "parser_value.hpp"


typedef std::map< std::string, Value > line_t;
typedef std::list< std::map< std::string, Value > * > lines_t;
typedef std::pair< std::string, Value > variable;


class Parser {
public:
  Parser();
  virtual
  ~Parser();
    
  virtual
  int handleError(const char *msg,
		  int first_line, int first_column,
		  int last_line, int last_column) = 0;
  double getVariable(std::string v, char *error);
  variable* newVariable(std::string* v, double n);
  Spline* getSpline(std::string key, char *error);
  void newSpline(variable *spline);
  
  line_t* newLine(variable* var);
  line_t* add2Line(line_t* vars, variable* var);
  lines_t* add2Lines(line_t* new_vars);
  
protected:
  lines_t *result;
  line_t *current_vars;
  line_t *current_splines;
  
};

#endif // PARSERTYPES_H
