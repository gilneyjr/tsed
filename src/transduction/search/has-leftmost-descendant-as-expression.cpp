#include "has-leftmost-descendant-as-expression.hpp"

Transduction::Search::HasLeftmostDescendantAsExpression::HasLeftmostDescendantAsExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasLeftmostDescendantAsExpression::~HasLeftmostDescendantAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasLeftmostDescendantAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->firstChild == nullptr)
    return false;

  auto leftmostDescendant = tree->firstChild;
  while (leftmostDescendant->firstChild != nullptr)
    leftmostDescendant = leftmostDescendant->firstChild;

  return expression->match(leftmostDescendant, symbolTable);
}
