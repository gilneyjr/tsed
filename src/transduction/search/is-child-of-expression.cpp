#include "is-child-of-expression.hpp"
#include "subtree-range-direction.hpp"

Transduction::Search::IsChildOfExpression::IsChildOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsChildOfExpression::match(Contexts::SearchMatchContext &context) const
{
  // TODO: should it be in validate method?
  if (expression->leftIsSubtreeRange())
    return false;

  return expression->match(Contexts::SearchMatchContext(
    context.current->getParent(),
    context.symbolTable,
    context.current->getParent()->isEndMarker(),
    context.matched
  ));
}
