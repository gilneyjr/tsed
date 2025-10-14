#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include "ast-node.hpp"
#include "nodename-match.hpp"
#include "replacement-node.hpp"
#include "symbol-table.hpp"
#include "syntax-tree.hpp"
#include "transversal-strategy.hpp"

namespace Transduction
{
  class Transducer
  {
  protected:
    TransversalStrategy* transversalStrategy;
  
    bool subtreeMatchesSearchExpression(SyntaxTree&, Ast::AstNode*, SymbolTable&);

    bool isParentOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isChildOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool hasNthChildAs(SyntaxTree&, Ast::AstNode*, unsigned int, SymbolTable&);
    bool isNthChildOf(SyntaxTree&, Ast::AstNode*, unsigned int, SymbolTable&);
    bool isImmediatelyLeftSiblingOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isImmediatelyRightSiblingOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool hasNthToLastChildAs(SyntaxTree&, Ast::AstNode*, unsigned int, SymbolTable&);
    bool isNthToLastChildOf(SyntaxTree&, Ast::AstNode*, unsigned int, SymbolTable&);
    bool hasUniqueChildAs(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isUniqueChildOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isAncestorOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isDescendantOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool hasLeftmostDescendantAs(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isLeftmostDescendantOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool hasRightmostDescendantAs(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isRightmostDescendantOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool hasUniquePathTo(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool hasUniquePathFrom(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isSiblingOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isLeftSiblingOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isRightSiblingOf(SyntaxTree&, Ast::AstNode*, SymbolTable&);
    bool isEqualTo(SyntaxTree&, Ast::AstNode*, SymbolTable&);

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