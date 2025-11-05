#include "has-leftmost-descendant-as-expression.hpp"

Transduction::Search::HasLeftmostDescendantAsExpression::HasLeftmostDescendantAsExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasLeftmostDescendantAsExpression::~HasLeftmostDescendantAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasLeftmostDescendantAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getFirstChild() == nullptr)
    return false;

  auto leftmostDescendant = tree->getFirstChild();
  while (leftmostDescendant->getFirstChild() != nullptr)
    leftmostDescendant = leftmostDescendant->getFirstChild();

  return expression->match(leftmostDescendant, symbolTable);
}
