#include "is-immediately-right-sibling-of-expression.hpp"

Transduction::Search::IsImmediatelyRightSiblingOfExpression::IsImmediatelyRightSiblingOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsImmediatelyRightSiblingOfExpression::~IsImmediatelyRightSiblingOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsImmediatelyRightSiblingOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->leftSibling == nullptr)
    return false;
  return expression->match(tree->leftSibling, symbolTable);
}
