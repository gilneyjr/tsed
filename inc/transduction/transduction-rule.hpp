#ifndef TRANSDUCTION_RULE_HPP
#define TRANSDUCTION_RULE_HPP

#include "search-expression.hpp"
#include "replacement-expression.hpp"

namespace Transduction
{
  class TransductionRule
  {
  private:
    Search::SearchExpression *searchExpression;
    Replacement::ReplacementExpression *replacementExpression;
  
  public:
    TransductionRule(
      Search::SearchExpression *searchExpression,
      Replacement::ReplacementExpression *replacementExpression
    );
    ~TransductionRule();
    Search::SearchExpression* getSearchExpression() const;
    Replacement::ReplacementExpression* getReplacementExpression() const;
  };
}

#endif
