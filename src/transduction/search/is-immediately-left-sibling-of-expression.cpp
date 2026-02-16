#include "is-immediately-left-sibling-of-expression.hpp"

Transduction::Search::IsImmediatelyLeftSiblingOfExpression::IsImmediatelyLeftSiblingOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsImmediatelyLeftSiblingOfExpression::match(Contexts::SearchMatchContext &context) const
{
  bool leftSiblingIsEndMarker = context.matched->getLeftSibling() == nullptr;
  auto leftSibling = leftSiblingIsEndMarker
    ? SyntaxTree::createEndMarkerOnLeftOf(context.matched)
    : context.matched->getLeftSibling(); 

  return expression->match(Contexts::SearchMatchContext(leftSibling, context.symbolTable, leftSiblingIsEndMarker));
}
