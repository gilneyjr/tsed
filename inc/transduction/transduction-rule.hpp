#ifndef TRANSDUCTION_RULE_HPP
#define TRANSDUCTION_RULE_HPP

#include "search-expression.hpp"
#include "replacement-tree.hpp"

namespace Transduction
{
  class TransductionRule
  {
  public:
    Transduction::Search::SearchExpression *search;
    Transduction::Replacement::TreeSequence *replacement;
    TransductionRule(Transduction::Search::SearchExpression*, Transduction::Replacement::TreeSequence*);
    ~TransductionRule();
  };
}

#endif
