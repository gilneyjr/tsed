#include "has-rightmost-descendant-as-expression.hpp"

Transduction::Search::HasRightmostDescendantAsExpression::HasRightmostDescendantAsExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}
  
bool Transduction::Search::HasRightmostDescendantAsExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker || context.matched->getLastChild() == nullptr)
    return false;

  auto rightmostDescendant = context.matched->getLastChild();
  while (rightmostDescendant->getLastChild() != nullptr)
    rightmostDescendant = rightmostDescendant->getLastChild();

  return expression->match(Contexts::SearchMatchContext(rightmostDescendant, context.symbolTable));
}

void Transduction::Search::HasRightmostDescendantAsExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"<<'\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}