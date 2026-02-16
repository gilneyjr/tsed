#include "has-unique-path-from-expression.hpp"

Transduction::Search::HasUniquePathFromExpression::HasUniquePathFromExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::HasUniquePathFromExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker
    || context.matched->getLeftSibling() != nullptr
    || context.matched->getRightSibling() != nullptr
  )
  {
    return false;
  }

  for (auto ancestor = context.matched->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
  {
    if (expression->match(Contexts::SearchMatchContext(ancestor, context.symbolTable)))
      return true;

    if (ancestor->getLeftSibling() != nullptr || ancestor->getRightSibling() != nullptr)
      return false;
  }

  return false;
}

void Transduction::Search::HasUniquePathFromExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \">>:\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
