#include "has-unique-path-to-expression.hpp"

Transduction::Search::HasUniquePathToExpression::HasUniquePathToExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::HasUniquePathToExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker)
    return false;

  for (auto descendant = context.matched->getFirstChild(); descendant != nullptr; descendant = descendant->getFirstChild())
  {
    if (descendant->getLeftSibling() != nullptr || descendant->getRightSibling() != nullptr)
      return false;

    if (expression->match(Contexts::SearchMatchContext(descendant, context.symbolTable)))
      return true;
  }

  return false;
}

void Transduction::Search::HasUniquePathToExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"<<:\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
