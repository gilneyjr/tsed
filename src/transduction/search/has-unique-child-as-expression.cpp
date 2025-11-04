#include "has-unique-child-as-expression.hpp"

Transduction::Search::HasUniqueChildAsExpression::HasUniqueChildAsExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasUniqueChildAsExpression::~HasUniqueChildAsExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasUniqueChildAsExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->firstChild == nullptr || tree->firstChild != tree->lastChild)
    return false;
  return expression->match(tree->parent, symbolTable);
}
