#include "is-sibling-of-expression.hpp"

Transduction::Search::IsSiblingOfExpression::IsSiblingOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsSiblingOfExpression::~IsSiblingOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsSiblingOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getParent() == nullptr)
    return false;

  for (auto sibling = tree->getParent()->getFirstChild(); sibling != nullptr; sibling = sibling->getRightSibling())
  {
    if (tree == sibling)
      continue;

    if (expression->match(sibling, symbolTable))
      return true;
  }

  return false;
}
