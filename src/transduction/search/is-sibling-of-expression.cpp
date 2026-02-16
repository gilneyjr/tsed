#include "is-sibling-of-expression.hpp"

Transduction::Search::IsSiblingOfExpression::IsSiblingOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsSiblingOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matched || context.matched->getParent() == nullptr)
    return false;

  for (auto sibling = context.matched->getParent()->getFirstChild(); sibling != nullptr; sibling = sibling->getRightSibling())
  {
    if (context.matched == sibling)
      continue;

    if (expression->match(Contexts::SearchMatchContext(sibling, context.symbolTable)))
      return true;
  }

  return false;
}

void Transduction::Search::IsSiblingOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"$\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
