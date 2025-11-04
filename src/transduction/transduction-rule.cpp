#include "transduction-rule.hpp"

Transduction::TransductionRule::TransductionRule(Transduction::Search::SearchExpression *search, Transduction::Replacement::TreeSequence *replacement)
  : search(search), replacement(replacement) {}

Transduction::TransductionRule::~TransductionRule()
{
  delete search;
  delete replacement;
}