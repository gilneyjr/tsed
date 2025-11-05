#include "is-nth-child-of-expression.hpp"

Transduction::Search::IsNthChildOfExpression::IsNthChildOfExpression(unsigned int n, SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), n(n), expression(expression) {}

Transduction::Search::IsNthChildOfExpression::~IsNthChildOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsNthChildOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getParent() == nullptr || tree->getParent()->getFirstChild() || n == 0u)
    return false;

  auto nthChildOfParent = tree->getParent()->getFirstChild();
  for (auto i = 1u; i < n; i++)
  {
    nthChildOfParent = nthChildOfParent->getRightSibling();
    if (nthChildOfParent == nullptr)
      return false;
  }

  return nthChildOfParent == tree && expression->match(tree->getParent(), symbolTable);
}
