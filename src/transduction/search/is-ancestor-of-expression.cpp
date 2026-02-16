#include <queue>
#include "is-ancestor-of-expression.hpp"

Transduction::Search::IsAncestorOfExpression::IsAncestorOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsAncestorOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker || context.matched->getFirstChild() == nullptr)
    return false;

  // TODO: should I use tree tranversal strategies here?
  std::queue<SyntaxTree*> queue;
  for (auto child = context.matched->getFirstChild(); child != nullptr; child = child->getRightSibling())
    queue.push(child);

  while (!queue.empty())
  {
    auto descendant = queue.front();
    queue.pop();

    if (expression->match(Contexts::SearchMatchContext(descendant, context.symbolTable)))
      return true;

    for (auto child = descendant->getFirstChild(); child != nullptr; child = child->getRightSibling())
      queue.push(child);
  }

  return false;
}

void Transduction::Search::IsAncestorOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"<<\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
