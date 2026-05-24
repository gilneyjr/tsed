#ifndef PARSING_RULES_HPP
#define PARSING_RULES_HPP

#include "nodename-expression.hpp"
#include "replacement-tree.hpp"
#include "replacement-tree-sequence.hpp"
#include "search-expression.hpp"
#include "transduction-rule.hpp"

namespace Parsing
{
  Transduction::Search::NodenameExpression* parseNodename(std::string &lexem);
  Transduction::Search::NodenameExpression* parseEndMarker();
  Transduction::Search::NodenameExpression* parseSubtreeRange(std::string &lexem);
  Transduction::Replacement::ReplacementTree* parseReplacementNode(const std::string &lexem);
  Transduction::Replacement::ReplacementTree* parseReplacementTree(
    Transduction::Replacement::ReplacementTree *root,
    Transduction::Replacement::ReplacementTreeSequence *children
  );
  Transduction::Replacement::ReplacementTreeSequence* parseReplacementTreeSequence(
    Transduction::Replacement::ReplacementTreeSequence *treeSequence,
    Transduction::Replacement::ReplacementTree *tree
  );
  Transduction::TransductionRule* parseTransduction(
    Transduction::Search::SearchExpression *searchExpression,
    Transduction::Replacement::ReplacementExpression *replacementExpression
  );
}

#endif
