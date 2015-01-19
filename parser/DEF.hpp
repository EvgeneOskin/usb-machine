#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <list>
#include "parsertypes.hpp"

#define INVALID_VAR 111111

double get_var(std::string v, line_t* current_vars);

variable* new_var(std::string* v, double n);

line_t* new_line(variable* var);
line_t* add_to_line(line_t* vars, variable* var);

lines_t* new_lines(line_t* new_vars,
		   line_t* current_vars);
lines_t* add_to_lines(line_t* new_vars,
		      lines_t* old_vars,
		      line_t* current_vars);

void new_spline(line_t *spline_storage, variable *spline);
Spline* get_spline(line_t *spline_storage, std::string key);

int yyerror(lines_t *l,
            line_t* current_vars,
            line_t* current_splines,
            const char *msg);
#endif // PARSER_H
