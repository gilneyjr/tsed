#include "is-rightmost-descendant-of-expression.hpp"

Transduction::Search::IsRightmostDescendantOfExpression::IsRightmostDescendantOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsRightmostDescendantOfExpression::~IsRightmostDescendantOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsRightmostDescendantOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->lastChild != nullptr || tree->firstChild != nullptr || tree->parent == nullptr)
    return false;

  for (auto ancestor = tree->parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (ancestor->rightSibling != nullptr) 
      return false;

    if (expression->match(ancestor, symbolTable))
      return true;
  }

  return false;
}
