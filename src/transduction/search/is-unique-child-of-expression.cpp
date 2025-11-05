#include "is-unique-child-of-expression.hpp"

Transduction::Search::IsUniqueChildOfExpression::IsUniqueChildOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsUniqueChildOfExpression::~IsUniqueChildOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsUniqueChildOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getParent() == nullptr || tree->getParent()->getFirstChild() == nullptr || tree->getParent()->getFirstChild() != tree->getParent()->getLastChild())
    return false;
  return expression->match(tree->getParent(), symbolTable);
}
