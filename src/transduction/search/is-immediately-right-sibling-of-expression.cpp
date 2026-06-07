#include "is-immediately-right-sibling-of-expression.hpp"

Transduction::Search::IsImmediatelyRightSiblingOfExpression::IsImmediatelyRightSiblingOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsImmediatelyRightSiblingOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (expression->leftIsSubtreeRange())
  {
    return expression->match(Contexts::SearchMatchContext(
      context.matched,
      context.symbolTable,
      context.matchedIsEndMarker,
      context.matched,
      Contexts::SubtreeRangeDirection::LEFT_SIBLINGS
    ));
  }

  return expression->match(Contexts::SearchMatchContext(
    context.matched->getLeftSibling(),
    context.symbolTable,
    context.matchedIsEndMarker,
    context.matched
  ));
}
