#include "is-rightmost-descendant-of-expression.hpp"

Transduction::Search::IsRightmostDescendantOfExpression::IsRightmostDescendantOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsRightmostDescendantOfExpression::~IsRightmostDescendantOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsRightmostDescendantOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getLastChild() != nullptr || tree->getFirstChild() != nullptr || tree->getParent() == nullptr)
    return false;

  for (auto ancestor = tree->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
  {
    if (ancestor->getRightSibling() != nullptr) 
      return false;

    if (expression->match(ancestor, symbolTable))
      return true;
  }

  return false;
}
