#include "is-left-sibling-of-expression.hpp"

Transduction::Search::IsLeftSiblingOfExpression::IsLeftSiblingOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsLeftSiblingOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker || context.matched->getParent() == nullptr)
    return false;

  for (auto leftSibling = context.matched->getParent()->getFirstChild(); leftSibling != nullptr && leftSibling != context.matched; leftSibling = leftSibling->getRightSibling())
    if (expression->match(Contexts::SearchMatchContext(leftSibling, context.symbolTable)))
      return true;
  return false;
}

void Transduction::Search::IsLeftSiblingOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"$..\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
