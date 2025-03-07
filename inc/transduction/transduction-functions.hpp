#ifndef TRANSDUCTION_FUNCTIONS_HPP
#define TRANSDUCTION_FUNCTIONS_HPP

#include <list>
#include <string>
#include <vector>

#include "ast-node.hpp"
#include "replacement-node.hpp"
#include "syntactic-tree.hpp"

namespace Transduction
{
  void applyTransductionRule(
    std::list<SyntacticTree*>&,
    Ast::AstNode*,
    std::vector<Ast::ReplacementNode*>*);

  void applyTransductionRule(
    SyntacticTree*,
    Ast::AstNode*,
    std::vector<Ast::ReplacementNode*>*);
  
  bool subtreeMatchesSearchExpression(
    SyntacticTree &tree,
    Ast::AstNode *searchExpression);

    bool isImmediatelyDominatedBy(SyntacticTree &searchPrimary, Ast::AstNode *searchExpression);

  bool tagMatchesPattern(const std::string&, const std::string&);
}

#endif