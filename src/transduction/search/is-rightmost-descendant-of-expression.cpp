#include "is-rightmost-descendant-of-expression.hpp"

Transduction::Search::IsRightmostDescendantOfExpression::IsRightmostDescendantOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsRightmostDescendantOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker
    || context.matched->getLastChild() != nullptr
    || context.matched->getFirstChild() != nullptr
    || context.matched->getRightSibling() != nullptr
    || context.matched->getParent() == nullptr
  )
  {
    return false;
  }

  for (auto ancestor = context.matched->getParent(); ancestor != nullptr; ancestor = ancestor->getParent())
  {
    if (ancestor->getRightSibling() != nullptr) 
      return false;

    if (expression->match(Contexts::SearchMatchContext(ancestor, context.symbolTable)))
      return true;
  }

  return false;
}

void Transduction::Search::IsRightmostDescendantOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \">>'\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
