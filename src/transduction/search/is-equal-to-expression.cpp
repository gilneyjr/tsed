#include "is-equal-to-expression.hpp"

Transduction::Search::IsEqualToExpression::IsEqualToExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsEqualToExpression::~IsEqualToExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsEqualToExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr)
    return false;
  // TODO: Check the correctness of this expression
  return expression->match(tree, symbolTable);
}
