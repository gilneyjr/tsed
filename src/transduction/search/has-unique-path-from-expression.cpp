#include "has-unique-path-from-expression.hpp"

Transduction::Search::HasUniquePathFromExpression::HasUniquePathFromExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasUniquePathFromExpression::~HasUniquePathFromExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasUniquePathFromExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->leftSibling != nullptr || tree->rightSibling != nullptr)
    return false;

  for (auto ancestor = tree->parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (expression->match(ancestor, symbolTable))
      return true;

    if (ancestor->leftSibling != nullptr || ancestor->rightSibling != nullptr)
      return false;
  }

  return false;
}
