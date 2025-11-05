#include "is-descendant-of-expression.hpp"

Transduction::Search::IsDescendantOfExpression::IsDescendantOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsDescendantOfExpression::~IsDescendantOfExpression()
{
  delete expression;
}

bool Transduction::Search::IsDescendantOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr)
    return false;

  for (auto ancestor = tree->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
    if (expression->match(ancestor, symbolTable))
      return true;
  return false;
}
