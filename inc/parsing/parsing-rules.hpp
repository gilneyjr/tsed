#ifndef PARSING_RULES_HPP
#define PARSING_RULES_HPP

#include "nodename-expression.hpp"
#include "replacement-tree.hpp"
#include "search-expression.hpp"
#include "transduction-rule.hpp"

namespace Parsing
{
  Transduction::Search::NodenameExpression* parseNodename(std::string&);
  Transduction::Search::NodenameExpression* parseEndMarker();
  Transduction::Search::NodenameExpression* parseSubtreeRange(std::string&);
  Transduction::Replacement::ReplacementTree* parseReplacementNode(const std::string&);
  Transduction::Replacement::ReplacementTree* parseReplacementTree(Transduction::Replacement::ReplacementTree*, Transduction::Replacement::TreeSequence*);
  Transduction::Replacement::TreeSequence* parseReplacementTreeSequence(Transduction::Replacement::TreeSequence*, Transduction::Replacement::ReplacementTree*);
  Transduction::TransductionRule* parseTransduction(Transduction::Search::SearchExpression*, Transduction::Replacement::TreeSequence*);
}

#endif
