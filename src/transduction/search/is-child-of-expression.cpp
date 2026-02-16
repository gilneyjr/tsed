#include "is-child-of-expression.hpp"

Transduction::Search::IsChildOfExpression::IsChildOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsChildOfExpression::match(Contexts::SearchMatchContext &context) const
{
  bool parentIsEndMarker = context.matched->getParent() == nullptr;
  auto parent = parentIsEndMarker
    ? SyntaxTree::createEndMarkerAbove(context.matched)
    : context.matched->getParent(); 

  return expression->match(Contexts::SearchMatchContext(parent, context.symbolTable, parentIsEndMarker));
}
