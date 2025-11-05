#include "is-right-sibling-of-expression.hpp"

Transduction::Search::IsRightSiblingOfExpression::IsRightSiblingOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsRightSiblingOfExpression::~IsRightSiblingOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsRightSiblingOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr)
    return false;

  for (auto rightSibling = tree->getRightSibling(); rightSibling != nullptr; rightSibling = rightSibling->getRightSibling())
    if (expression->match(rightSibling, symbolTable))
      return true;

  return false;
}
