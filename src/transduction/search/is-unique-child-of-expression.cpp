#include "is-unique-child-of-expression.hpp"

Transduction::Search::IsUniqueChildOfExpression::IsUniqueChildOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsUniqueChildOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker
    || context.matched->getParent() == nullptr
    || context.matched->getLeftSibling() != nullptr
    || context.matched->getRightSibling() != nullptr
  )
  {
    return false;
  }

  return expression->match(Contexts::SearchMatchContext(context.matched->getParent(), context.symbolTable));
}

void Transduction::Search::IsUniqueChildOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \">:\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
