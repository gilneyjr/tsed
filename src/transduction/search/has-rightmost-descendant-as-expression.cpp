#include "has-rightmost-descendant-as-expression.hpp"

Transduction::Search::HasRightmostDescendantAsExpression::HasRightmostDescendantAsExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasRightmostDescendantAsExpression::~HasRightmostDescendantAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasRightmostDescendantAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getLastChild() == nullptr)
    return false;

  auto rightmostDescendant = tree->getLastChild();
  while (rightmostDescendant->getLastChild() != nullptr)
    rightmostDescendant = rightmostDescendant->getLastChild();

  return expression->match(rightmostDescendant, symbolTable);
}
