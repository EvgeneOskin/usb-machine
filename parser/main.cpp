#include "Parser.hpp"
#include <iostream>
#include "cstdio"
#include <memory>


class ParserImpl : public Parser {
  int handleError(const char *msg,
                   int first_line, int first_column,
                   int last_line, int last_column) {
    std::cout << msg << " " << first_line << ":" << first_column
              << " - " << last_line << ":" << last_column << "\n";
    return 0;
  }
};

int main() {
  Parser* parser = new ParserImpl();
  FILE * f = fopen("test_template.dat", "r");

  std::cout << "Hello, my master.\n";
  yyrestart(f);
  yyparse(parser);
  fclose(f);
  std::cout << "Closed\n";
  delete parser;
  return 0;
}
