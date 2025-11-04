#ifndef PARSING_RULES_HPP
#define PARSING_RULES_HPP

#include "nodename-expression.hpp"
#include "replacement-leaf-node.hpp"
#include "replacement-tree.hpp"
#include "search-expression.hpp"
#include "transduction-rule.hpp"

namespace Parsing
{
  Transduction::Search::NodenameExpression* parseNodename(std::string&);
  Transduction::Search::NodenameExpression* parseEndMarker();
  Transduction::Search::NodenameExpression* parseSubtreeRange(std::string&);
  Transduction::Search::SearchExpression* parseRestriction(std::string&, Transduction::Search::SearchExpression*);
  Transduction::Search::SearchExpression* parseNot(Transduction::Search::SearchExpression*);
  Transduction::Search::SearchExpression* parseAnd(Transduction::Search::SearchExpression*, Transduction::Search::SearchExpression*);
  Transduction::Search::SearchExpression* parseOr(Transduction::Search::SearchExpression*, Transduction::Search::SearchExpression*);
  Transduction::Search::SearchExpression* parseSearchExpression(Transduction::Search::NodenameExpression*, Transduction::Search::SearchExpression*);
  Transduction::Replacement::ReplacementLeafNode* parseReplacementNode(const std::string&, const Nodename::NodenameInfoSet&);
  Transduction::Replacement::ReplacementTree* parseReplacementTree(Transduction::Replacement::ReplacementLeafNode*, Transduction::Replacement::TreeSequence*);
  Transduction::Replacement::TreeSequence* parseReplacementTreeSequence(Transduction::Replacement::TreeSequence*, Transduction::Replacement::ReplacementTree*);
  Transduction::TransductionRule* parseTransduction(Transduction::Search::SearchExpression*, Transduction::Replacement::TreeSequence*);
}

#endif
