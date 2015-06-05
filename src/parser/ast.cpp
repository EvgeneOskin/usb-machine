#include "ast.h"
#include "grammar_yacc.h"
#include <iostream>

AST::AST(double d) {
  this->mLeft = NULL;
  this->mRight = NULL;
  this->mType = ast_num;

  this->mValue = new Value(d);
}

AST::AST(Spline *spline) {
  this->mLeft = NULL;
  this->mRight = NULL;
  this->mType = ast_spline;

  this->mValue = new Value(spline);
}

AST::AST(std::string s) {
  this->mLeft = NULL;
  this->mRight = NULL;
  this->mType = ast_var;
  this->mValue = NULL;
  this->mKey = s;
}

AST::AST(AST* left, AST* right, int operation) {
  this->mLeft = left;
  this->mRight = right;
  this->mType = ast_com;
  this->mValue = NULL;
  this->mOperation = operation;
}

AST::AST(AST* ast, int operation) {
  this->mLeft = ast;
  this->mRight = NULL;
  this->mType = ast_com;
  this->mValue = NULL;
  this->mOperation = operation;
}

double eval(AST *ast, Parser* parser, char *error) {
  double left = 0.0;
  double right = 0.0;

  if (ast->mRight != NULL) {
    right = eval(ast->mRight, parser, error);
  }
  if (ast->mLeft != NULL) {
    left = eval(ast->mLeft, parser, error);
  }
  if (*error) {
    return 0.0;
  }

  switch(ast->mType){
  case ast_var:
    return parser->getVariable(ast->mKey, error);
  case ast_num:
    return ast->mValue->get_number();
  case ast_com:
    switch(ast->mOperation) {
    case PLUS:
      return left + right;
    case MINUS:
      return left - right;
    case MULT:
      return left * right;
    case DIVI:
      if (right == 0.0) {
        // TODO Need add correct columns and lines
        parser->handleError("Divide by zero!", -1, -1, -1, -1);
        *error = 1;
        return 0.0;
      }
      return left / right;
    case SIN:
      return sin(left);
    case COS:
      return cos(left);
    case TAN:
      return tan(left);

    case ASIN:
      return asin(left);
    case ACOS:
      return acos(left);
    case ATAN:
      return atan(left);

    case SINH:
      return sinh(left);
    case COSH:
      return cosh(left);
    case TANH:
      return tanh(left);

    case ASINH:
      return asinh(left);
    case ACOSH:
      return acosh(left);
    case ATANH:
      return atanh(left);

    case EXP:
      return exp(left);
    case LOG:
      if (left <= 0.0) {
        // TODO Need add correct columns and lines
        parser->handleError("Log from not positive argument!", -1, -1, -1, -1);
        *error = 1;
        return 0.0;
      }
      return log(left);
    case LOG10:
      if (left <= 0.0) {
        // TODO Need add correct columns and lines
        parser->handleError("Log from not positive argument!", -1, -1, -1, -1);
        *error = 1;
        return 0.0;
      }
      return log10(left);
    case SQRT:
      if (left < 0.0) {
        // TODO Need add correct columns and lines
        parser->handleError("Sqrt from negative value!", -1, -1, -1, -1);
        *error = 1;
        return 0.0;
      }
      return sqrt(left);
    case FABS:
      return fabs(left);
    case POW:
      return pow(left, right);
    }
  }
  // TODO Need add correct columns and lines
  parser->handleError("Unkown action!", -1, -1, -1, -1);
  *error = 1;
  return 0.0;
}

ast_line_t* new_ast_line(ast_variable_t* var) {
  ast_line_t * line = new ast_line_t();
  return add_to_ast_line(line, var);
}

ast_line_t* add_to_ast_line(ast_line_t * line, ast_variable_t* var) {
  line->insert(*var);
  return line;
}

ast_lines_t*  new_ast_lines(ast_line_t* new_vars) {
  ast_lines_t* lines = new ast_lines_t();
  return add_to_ast_lines(new_vars, lines);
}

ast_lines_t* add_to_ast_lines(ast_line_t* new_vars,
                  ast_lines_t* old_vars) {
  old_vars->push_back(new_vars);
  return old_vars;
}
