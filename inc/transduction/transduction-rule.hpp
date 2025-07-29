#ifndef TRANSDUCTION_RULE_HPP
#define TRANSDUCTION_RULE_HPP

#include <vector>
#include "ast-node.hpp"
#include "replacement-node.hpp"

namespace Transduction
{
  struct TransductionRule
  {
    Ast::AstNode *search;
    std::vector<Ast::ReplacementNode*> *replacement;
  };
}

#endif