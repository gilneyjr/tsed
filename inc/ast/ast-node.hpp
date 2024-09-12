#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <string>
#include "ast-info.hpp"

namespace Ast 
{
  class AstNode
  {
  public:
    AstNode* parent;
    AstNode* left;
    AstNode* right;

    std::string name; // TODO: ver se precisa manter isso depois

    AstInfo info;

    AstNode(AstNode* parent, AstNode* left, AstNode* right, AstInfo info, std::string name = "");
    ~AstNode();
  };
}

// TODO: Remove it later
// Witch are the informations will be stored in AstNode?
// - nodename => nodenameInfo
// - end_marker => nodenameInfo (or another thing ???)
// - op search_second => what operador is it
// - terminal_not restrictions_not => what operador is it, what defined nodenames are

#endif
