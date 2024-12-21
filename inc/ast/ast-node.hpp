#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include "ast-node-data.hpp"
#include "ast-node-type.hpp"

namespace Ast
{
  class AstNode
  {
  public: // TODO: Change to protected later
    AstNode* parent;
    AstNode* left;
    AstNode* right;

    AstNodeType type;
    AstNodeData data;

  public:
    AstNode(
      AstNode* parent,
      AstNode* left,
      AstNode* right,
      Nodename::NodenameInfo* info
    );

    AstNode(
      AstNode* parent,
      AstNode* left,
      AstNode* right,
      std::string &operation,
      Nodename::NodenameInfoSet &definitions,
      Nodename::NodenameInfoSet &references
    );

    ~AstNode();

    AstNode* getLeft();
    void setLeft(AstNode* left);
    AstNode* getRight();
    void setRight(AstNode* right);
    AstNode* getParent();
    bool isLeaf();
    bool isInternal();
  };
}

#endif
