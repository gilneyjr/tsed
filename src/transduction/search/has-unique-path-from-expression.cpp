#include "has-unique-path-from-expression.hpp"

Transduction::Search::HasUniquePathFromExpression::HasUniquePathFromExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasUniquePathFromExpression::~HasUniquePathFromExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasUniquePathFromExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getLeftSibling() != nullptr || tree->getRightSibling() != nullptr)
    return false;

  for (auto ancestor = tree->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
  {
    if (expression->match(ancestor, symbolTable))
      return true;

    if (ancestor->getLeftSibling() != nullptr || ancestor->getRightSibling() != nullptr)
      return false;
  }

  return false;
}
