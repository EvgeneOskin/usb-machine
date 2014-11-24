#include "Parser.hpp"
#include <iostream>
#include "cstdio"
#include "DEF.hpp"

extern void yyrestart(FILE*);
extern int yyparse (lines_t *result, line_t *current_vars, line_t *current_splines);


int main() {
  lines_t *result = new lines_t();
  line_t *current_vars = new line_t();
  line_t *current_spline = new line_t();
  FILE * f = fopen("test_template.dat", "r");

  std::cout << "Hello, my master.\n";
  yyrestart(f);
  yyparse(result, current_vars, current_spline);
  fclose(f);
  std::cout << "Closed\n";
  return 0;
}
