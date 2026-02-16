#include "is-right-sibling-of-expression.hpp"

Transduction::Search::IsRightSiblingOfExpression::IsRightSiblingOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsRightSiblingOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker)
    return false;

  for (auto rightSibling = context.matched->getRightSibling(); rightSibling != nullptr; rightSibling = rightSibling->getRightSibling())
    if (expression->match(Contexts::SearchMatchContext(rightSibling, context.symbolTable)))
      return true;

  return false;
}

void Transduction::Search::IsRightSiblingOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"$,,\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
