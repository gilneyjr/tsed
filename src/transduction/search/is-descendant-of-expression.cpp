#include "is-descendant-of-expression.hpp"

Transduction::Search::IsDescendantOfExpression::IsDescendantOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsDescendantOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker)
    return false;

  for (auto ancestor = context.matched->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
    if (expression->match(Contexts::SearchMatchContext(ancestor, context.symbolTable)))
      return true;
  return false;
}

void Transduction::Search::IsDescendantOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \">>\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
