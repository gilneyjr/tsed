#include "has-unique-path-to-expression.hpp"

Transduction::Search::HasUniquePathToExpression::HasUniquePathToExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::HasUniquePathToExpression::~HasUniquePathToExpression()
{
  delete expression;
}
  
bool Transduction::Search::HasUniquePathToExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr)
    return false;

  for (auto descendant = tree->firstChild; descendant != nullptr; descendant = descendant->firstChild)
  {
    if (descendant->leftSibling != nullptr || descendant->rightSibling != nullptr)
      return false;

    if (expression->match(descendant, symbolTable))
      return true;
  }

  return false;
}
