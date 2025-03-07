#ifndef TRANSDUCTION_FUNCTIONS_HPP
#define TRANSDUCTION_FUNCTIONS_HPP

#include <list>
#include <string>
#include <vector>

#include "ast-node.hpp"
#include "replacement-node.hpp"
#include "syntax-tree.hpp"

namespace Transduction
{
  void applyTransductionRule(
    std::list<SyntaxTree*>&,
    Ast::AstNode*,
    std::vector<Ast::ReplacementNode*>*);

  void applyTransductionRule(
    SyntaxTree*,
    Ast::AstNode*,
    std::vector<Ast::ReplacementNode*>*);
  
  bool subtreeMatchesSearchExpression(
    SyntaxTree &tree,
    Ast::AstNode *searchExpression);

    bool isImmediatelyDominatedBy(SyntaxTree &searchPrimary, Ast::AstNode *searchExpression);

  bool tagMatchesPattern(const std::string&, const std::string&);
}

#endif