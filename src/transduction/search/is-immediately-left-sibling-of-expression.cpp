#include "is-immediately-left-sibling-of-expression.hpp"

Transduction::Search::IsImmediatelyLeftSiblingOfExpression::IsImmediatelyLeftSiblingOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsImmediatelyLeftSiblingOfExpression::~IsImmediatelyLeftSiblingOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsImmediatelyLeftSiblingOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->rightSibling == nullptr)
    return false;
  return expression->match(tree->rightSibling, symbolTable);
}
