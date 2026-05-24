#include "transduction-rule.hpp"

Transduction::TransductionRule::TransductionRule(
  Search::SearchExpression *searchExpression,
  Replacement::ReplacementExpression *replacementExpression
) : searchExpression(searchExpression), replacementExpression(replacementExpression) {}

Transduction::TransductionRule::~TransductionRule()
{
  delete searchExpression;
  delete replacementExpression;
}

Transduction::Search::SearchExpression *Transduction::TransductionRule::getSearchExpression() const
{
  return searchExpression;
}

Transduction::Replacement::ReplacementExpression *Transduction::TransductionRule::getReplacementExpression() const
{
  return replacementExpression;
}
