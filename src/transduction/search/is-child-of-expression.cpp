#include "is-child-of-expression.hpp"

Transduction::Search::IsChildOfExpression::IsChildOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsChildOfExpression::~IsChildOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsChildOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr) // TODO: Implement end marker on left case later
    return false;
  return expression->match(tree->parent, symbolTable);
}
