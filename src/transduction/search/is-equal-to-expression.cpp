#include "is-equal-to-expression.hpp"

Transduction::Search::IsEqualToExpression::IsEqualToExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsEqualToExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker)
    return false;
  // TODO: think of a way to implement this, as this doesn't yet consider an exact match
  return expression->match(context);
}

void Transduction::Search::IsEqualToExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"=\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}