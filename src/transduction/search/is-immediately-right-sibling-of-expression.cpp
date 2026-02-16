#include "is-immediately-right-sibling-of-expression.hpp"

Transduction::Search::IsImmediatelyRightSiblingOfExpression::IsImmediatelyRightSiblingOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsImmediatelyRightSiblingOfExpression::match(Contexts::SearchMatchContext &context) const
{
  bool rightSiblingIsEndMarker = context.matched->getRightSibling() == nullptr;
  auto rightSibling = rightSiblingIsEndMarker
    ? SyntaxTree::createEndMarkerOnRightOf(context.matched)
    : context.matched->getRightSibling(); 

  return expression->match(Contexts::SearchMatchContext(rightSibling, context.symbolTable, rightSiblingIsEndMarker));
}
