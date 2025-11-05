#include <queue>
#include "is-ancestor-of-expression.hpp"

Transduction::Search::IsAncestorOfExpression::IsAncestorOfExpression(SearchExpression *expression)
  : SearchExpression(expression->getDefinitions(), expression->getReferences()), expression(expression) {}

Transduction::Search::IsAncestorOfExpression::~IsAncestorOfExpression()
{
  delete expression;
}
  
bool Transduction::Search::IsAncestorOfExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (tree == nullptr || tree->getFirstChild() == nullptr)
    return false;

  // TODO: should I use tree tranversal strategies here?
  std::queue<SyntaxTree*> queue;
  for (auto child = tree->getFirstChild(); child != nullptr; child = child->getRightSibling())
    queue.push(child);

  while (!queue.empty())
  {
    auto descendant = queue.front();
    queue.pop();

    if (expression->match(descendant, symbolTable))
      return true;

    for (auto child = descendant->getFirstChild(); child != nullptr; child = child->getRightSibling())
      queue.push(child);
  }

  return false;
}
