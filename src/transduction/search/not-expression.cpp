#include "not-expression.hpp"

Transduction::Search::NotExpression::NotExpression(SearchExpression *expression)
  : expression(expression) {}

Transduction::Search::NotExpression::~NotExpression()
{
  delete expression;
}
  
bool Transduction::Search::NotExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  symbolTable.enterScope();
  bool matched = !expression->match(tree, symbolTable);
  symbolTable.exitScope(); // all matches found in negation are discarded
  return matched;
}
