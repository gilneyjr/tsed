#include "is-left-sibling-of-expression.hpp"

Transduction::Search::IsLeftSiblingOfExpression::IsLeftSiblingOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsLeftSiblingOfExpression::~IsLeftSiblingOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsLeftSiblingOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getParent() == nullptr)
    return false;

  for (auto leftSibling = tree->getParent()->getFirstChild(); leftSibling != nullptr && leftSibling != tree; leftSibling = leftSibling->getRightSibling())
    if (expression->match(leftSibling, symbolTable))
      return true;

  return false;
}
