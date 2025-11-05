#include "is-leftmost-descendant-of-expression.hpp"

Transduction::Search::IsLeftmostDescendantOfExpression::IsLeftmostDescendantOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsLeftmostDescendantOfExpression::~IsLeftmostDescendantOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsLeftmostDescendantOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getLastChild() != nullptr || tree->getFirstChild() != nullptr || tree->getParent() == nullptr)
    return false;

  for (auto ancestor = tree->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
  {
    if (ancestor->getLeftSibling() != nullptr) 
      return false;

    if (expression->match(ancestor, symbolTable))
      return true;
  }

  return false;
}
