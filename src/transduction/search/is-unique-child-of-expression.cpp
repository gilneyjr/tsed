#include "is-unique-child-of-expression.hpp"

Transduction::Search::IsUniqueChildOfExpression::IsUniqueChildOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsUniqueChildOfExpression::~IsUniqueChildOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsUniqueChildOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->parent == nullptr || tree->parent->firstChild == nullptr || tree->parent->firstChild != tree->parent->lastChild)
    return false;
  return expression->match(tree->parent, symbolTable);
}
