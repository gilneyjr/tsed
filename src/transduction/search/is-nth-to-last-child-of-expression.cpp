#include "is-nth-to-last-child-of-expression.hpp"

Transduction::Search::IsNthToLastChildOfExpression::IsNthToLastChildOfExpression(unsigned int n, Transduction::Search::SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), n(n), expression(expression) {}

Transduction::Search::IsNthToLastChildOfExpression::~IsNthToLastChildOfExpression()
{
  delete expression;
}

bool Transduction::Search::IsNthToLastChildOfExpression::match(Transduction::SyntaxTree *tree, Transduction::SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->parent == nullptr || tree->parent->lastChild == nullptr || n == 0)
    return false;

  auto nthToLastChildOfParent = tree->parent->lastChild;
  for (auto i = n; i > 1u; i--)
  {
    nthToLastChildOfParent = nthToLastChildOfParent->leftSibling;
    if (nthToLastChildOfParent == nullptr)
      return false;
  }

  return nthToLastChildOfParent == tree && expression->match(tree, symbolTable);
}