#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include <list>
#include <string>
#include <vector>

#include "ast-node.hpp"
#include "replacement-node.hpp"
#include "syntax-tree.hpp"
#include "transversal-strategy.hpp"

namespace Transduction
{
  class Transducer
  {
  protected:
    TransversalStrategy* transversalStrategy;
  
    bool subtreeMatchesSearchExpression(SyntaxTree &tree, Ast::AstNode *searchExpression);

    bool isImmediatelyDominatedBy(SyntaxTree &searchPrimary, Ast::AstNode *searchExpression);
  
    bool tagMatchesPattern(const std::string&, const std::string&);

  public:
    Transducer(TransversalStrategy*);
    ~Transducer();

    void applyTransductionRule(
      std::list<SyntaxTree*>&,
      Ast::AstNode*,
      std::vector<Ast::ReplacementNode*>*);
  
    void applyTransductionRule(
      SyntaxTree*,
      Ast::AstNode*,
      std::vector<Ast::ReplacementNode*>*);
  };
}

#endif