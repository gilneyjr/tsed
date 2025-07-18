#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include "ast-node.hpp"
#include "nodename-match.hpp"
#include "replacement-node.hpp"
#include "syntax-tree.hpp"
#include "transversal-strategy.hpp"

namespace Transduction
{
  class Transducer
  {
  protected:
    TransversalStrategy* transversalStrategy;
  
    bool subtreeMatchesSearchExpression(
      SyntaxTree &tree,
      Ast::AstNode *searchExpression,
      std::map<int, Transduction::NodenameMatch>&
    );

    bool isImmediatelyDominatedBy(
      SyntaxTree &searchPrimary,
      Ast::AstNode *searchExpression,
      std::map<int, Transduction::NodenameMatch>&
    );
  
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