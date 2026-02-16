#include "is-leftmost-descendant-of-expression.hpp"

Transduction::Search::IsLeftmostDescendantOfExpression::IsLeftmostDescendantOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsLeftmostDescendantOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker
    || context.matched->getLastChild() != nullptr
    || context.matched->getFirstChild() != nullptr
    || context.matched->getParent() == nullptr
  )
  {
    return false;
  }

  for (auto ancestor = context.matched->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
  {
    if (ancestor->getLeftSibling() != nullptr) 
      return false;

    if (expression->match(Contexts::SearchMatchContext(ancestor, context.symbolTable)))
      return true;
  }

  return false;
}

void Transduction::Search::IsLeftmostDescendantOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \">>,\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
