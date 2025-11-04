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
  if (tree == nullptr || tree->firstChild == nullptr)
    return false;

  // TODO: should I use tree tranversal strategies here?
  std::queue<SyntaxTree*> queue;
  for (auto child = tree->firstChild; child != nullptr; child = child->rightSibling)
    queue.push(child);

  while (!queue.empty())
  {
    auto descendant = queue.front();
    queue.pop();

    if (expression->match(descendant, symbolTable))
      return true;

    for (auto child = descendant->firstChild; child != nullptr; child = child->rightSibling)
      queue.push(child);
  }

  return false;
}
