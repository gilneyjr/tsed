#include "is-parent-of-expression.hpp"

Transduction::Search::IsParentOfExpression::IsParentOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsParentOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (expression->leftIsSubtreeRange())
  {
    return expression->match(Contexts::SearchMatchContext(
      context.matched,
      context.symbolTable,
      context.matchedIsEndMarker,
      context.matched,
      Contexts::SubtreeRangeDirection::CHILDREN
    ));
  }

  for (auto child = context.matched->getFirstChild(); child != nullptr && !child->isEndMarker(); child = child->getRightSibling())
    if (expression->match(Contexts::SearchMatchContext(child, context.symbolTable, context.matchedIsEndMarker, context.matched)))
      return true;
  return false;
}
