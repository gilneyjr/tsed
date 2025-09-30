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
  
    bool subtreeMatchesSearchExpression(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);

    bool isParentOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isChildOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool hasNthChildAs(SyntaxTree&, Ast::AstNode*, unsigned int, std::map<int, Transduction::NodenameMatch>&);
    bool isNthChildOf(SyntaxTree&, Ast::AstNode*, unsigned int, std::map<int, Transduction::NodenameMatch>&);
    bool isImmediatelyLeftSiblingOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isImmediatelyRightSiblingOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool hasNthToLastChildAs(SyntaxTree&, Ast::AstNode*, unsigned int, std::map<int, Transduction::NodenameMatch>&);
    bool isNthToLastChildOf(SyntaxTree&, Ast::AstNode*, unsigned int, std::map<int, Transduction::NodenameMatch>&);
    bool hasUniqueChildAs(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isUniqueChildOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isAncestorOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isDescendantOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool hasLeftmostDescendantAs(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isLeftmostDescendantOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool hasRightmostDescendantAs(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool isRightmostDescendantOf(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool hasUniquePathTo(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);
    bool hasUniquePathFrom(SyntaxTree&, Ast::AstNode*, std::map<int, Transduction::NodenameMatch>&);

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