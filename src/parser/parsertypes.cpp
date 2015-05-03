#include <iostream>
#include "stdlib.h"
#include <string>

#include "parsertypes.h"
#include "grammar_yacc.h"

Parser::Parser() {
  result = new lines_t();
  current_vars = new line_t();
  current_splines = new line_t();
}

Parser::~Parser() {
  delete result;
  delete current_vars;
  delete current_splines;
}


line_t* Parser::newLine(variable* var) {
  line_t * vars = new line_t();
  return add2Line(vars, var);
}

line_t* Parser::add2Line(line_t * line, variable* var) {
  line->insert(*var);
  return line;
}

lines_t* Parser::add2Lines(line_t* new_vars) {
  result->push_back(new_vars);
  for(line_t::iterator i = new_vars->begin();
      i != new_vars->end();
      ++i){
    current_vars->erase(i->first);
    current_vars->insert(*i);
  }
  return result;
}

double Parser::getVariable(std::string v, char *error) {
  for (line_t::iterator i = current_vars->begin();
       i != current_vars->end();
       ++i) {
    if (i->first.compare(v) == 0){
      return i->second.get_number();
    }
  }
  // TODO Need add columns liness.
  handleError("Can not find variable", -1, -1, -1, -1);
  *error = 1;
  return 0.0;
}

void Parser::newSpline(variable *spline) {
  current_splines->insert(*spline);
}

Spline* Parser::getSpline(std::string key, char *error) {
  for (line_t::iterator i = current_splines->begin();
       i != current_splines->end();
       ++i) {
    if (i->first.compare(key) == 0){
      std::cout << "get spline" << "\n";
      return i->second.get_spline();
    }
  }
  // TODO Need add columns and lines.
  handleError("Can not find spline", -1, -1, -1, -1);
  *error = 1;
  return NULL;
}
