#include "has-rightmost-descendant-as-expression.hpp"

Transduction::Search::HasRightmostDescendantAsExpression::HasRightmostDescendantAsExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasRightmostDescendantAsExpression::~HasRightmostDescendantAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasRightmostDescendantAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->lastChild == nullptr)
    return false;

  auto rightmostDescendant = tree->lastChild;
  while (rightmostDescendant->lastChild != nullptr)
    rightmostDescendant = rightmostDescendant->lastChild;

  return expression->match(rightmostDescendant, symbolTable);
}
