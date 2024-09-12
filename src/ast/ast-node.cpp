#include "ast-node.hpp"

Ast::AstNode::AstNode(AstNode* parent, AstNode* left, AstNode* right, AstInfo info, std::string name)
{
  this->parent = parent;
  this->left = left;
  this->right = right;
  this->info = info;
  this->name = name;
}

Ast::AstNode::~AstNode()
{
  if (left == nullptr && right == nullptr)
    delete info.nodenameInfo;
  else
    delete info.definedNodenames;

  delete left;
  delete right;
}