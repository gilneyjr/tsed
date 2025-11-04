#include "is-nth-child-of-expression.hpp"

Transduction::Search::IsNthChildOfExpression::IsNthChildOfExpression(unsigned int n, SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), n(n), expression(expression) {}

Transduction::Search::IsNthChildOfExpression::~IsNthChildOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsNthChildOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->parent == nullptr || tree->parent->firstChild || n == 0u)
    return false;

  auto nthChildOfParent = tree->parent->firstChild;
  for (auto i = 1u; i < n; i++)
  {
    nthChildOfParent = nthChildOfParent->rightSibling;
    if (nthChildOfParent == nullptr)
      return false;
  }

  return nthChildOfParent == tree && expression->match(tree->parent, symbolTable);
}
