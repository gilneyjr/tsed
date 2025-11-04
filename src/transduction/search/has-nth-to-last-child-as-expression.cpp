#include "has-nth-to-last-child-as-expression.hpp"

Transduction::Search::HasNthToLastChildAsExpression::HasNthToLastChildAsExpression(unsigned int n, SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), n(n), expression(expression) {}

Transduction::Search::HasNthToLastChildAsExpression::~HasNthToLastChildAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasNthToLastChildAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->lastChild == nullptr || n == 0)
    return false;

  auto nthChild = tree->lastChild;
  for (auto i = 1u; i < n; i++)
  {
    nthChild = nthChild->rightSibling;
    if (nthChild == nullptr)
      return false;
  }

  return expression->match(nthChild, symbolTable);
}
