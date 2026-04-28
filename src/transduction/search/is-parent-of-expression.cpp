#include "is-parent-of-expression.hpp"

Transduction::Search::IsParentOfExpression::IsParentOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsParentOfExpression::match(Contexts::SearchMatchContext &context) const
{
  for (auto child = context.matched->getFirstChild(); child != nullptr && !child->isEndMarker(); child = child->getRightSibling())
    if (expression->match(Contexts::SearchMatchContext(child, context.symbolTable, context.matchedIsEndMarker, context.matched)))
      return true;
  return false;
}
