#include "has-nth-child-as-expression.hpp"

Transduction::Search::HasNthChildAsExpression::HasNthChildAsExpression(unsigned int n, SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), n(n), expression(expression) {}

Transduction::Search::HasNthChildAsExpression::~HasNthChildAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasNthChildAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getFirstChild() == nullptr || n == 0)
    return false;

  auto nthChild = tree->getFirstChild();
  for (auto i = 1u; i < n; i++)
  {
    nthChild = nthChild->getRightSibling();
    if (nthChild == nullptr)
      return false;
  }

  return expression->match(nthChild, symbolTable);
}
