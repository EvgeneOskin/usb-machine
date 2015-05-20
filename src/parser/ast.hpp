#ifndef AST_H
#define AST_H

#include "parsertypes.hpp"
#include "parserspline.hpp"

typedef enum {
  ast_var,
  ast_num,
  ast_com,
  ast_spline
} e_AST;

class AST {

public:
  AST(std::string s);
  AST(double d);
  AST(Spline *spline);
  AST(AST* left, AST* right, int mOperation);
  AST(AST* ast, int mOperation);

  AST* mLeft;
  AST* mRight;
  Value* mValue;
  std::string mKey;
  int mOperation;
  e_AST mType;
};

double eval(AST *ast, Parser* parser, char* error);

typedef std::pair< std::string, AST* > ast_variable_t;
typedef std::map< std::string, AST* > ast_line_t;
typedef std::list< std::map< std::string, AST* > * > ast_lines_t;

ast_line_t* new_ast_line(ast_variable_t* var);
ast_line_t* add_to_ast_line(ast_line_t * line, ast_variable_t* var);
ast_lines_t* new_ast_lines(ast_line_t* new_vars);
ast_lines_t* add_to_ast_lines(ast_line_t* new_vars,
			      ast_lines_t* old_vars);
#endif //AST_H
