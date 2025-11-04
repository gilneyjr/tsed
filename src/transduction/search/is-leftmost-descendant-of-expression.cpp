#include "is-leftmost-descendant-of-expression.hpp"

Transduction::Search::IsLeftmostDescendantOfExpression::IsLeftmostDescendantOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsLeftmostDescendantOfExpression::~IsLeftmostDescendantOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsLeftmostDescendantOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->lastChild != nullptr || tree->firstChild != nullptr || tree->parent == nullptr)
    return false;

  for (auto ancestor = tree->parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (ancestor->leftSibling != nullptr) 
      return false;

    if (expression->match(ancestor, symbolTable))
      return true;
  }

  return false;
}
