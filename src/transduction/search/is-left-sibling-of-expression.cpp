#include "is-left-sibling-of-expression.hpp"

Transduction::Search::IsLeftSiblingOfExpression::IsLeftSiblingOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsLeftSiblingOfExpression::~IsLeftSiblingOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsLeftSiblingOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->parent == nullptr)
    return false;

  for (auto leftSibling = tree->parent->firstChild; leftSibling != nullptr && leftSibling != tree; leftSibling = leftSibling->rightSibling)
    if (expression->match(leftSibling, symbolTable))
      return true;

  return false;
}
