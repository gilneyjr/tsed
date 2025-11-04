#include "is-parent-of-expression.hpp"

Transduction::Search::IsParentOfExpression::IsParentOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsParentOfExpression::~IsParentOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsParentOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr) // TODO: Implement end marker on left case later
    return false;

  if (tree->firstChild == nullptr)
    return expression->match(nullptr, symbolTable); // try to match end marker

  for (auto child = tree->firstChild; child != nullptr; child = child->rightSibling)
    if (expression->match(child, symbolTable))
      return true;
  return false;
}
