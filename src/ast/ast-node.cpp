#include "ast-node.hpp"

Ast::AstNode::AstNode(AstNode* parent, AstNode* left, AstNode* right, AstInfo info, std::string name)
{
  this->parent = parent;
  this->left = left;
  this->right = right;
  this->info = info;
  this->name = name;

  if (left != nullptr)
    left->parent = this;
  if (right != nullptr)
    right->parent = this;
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


Ast::AstNode* Ast::AstNode::getLeftChild()
{
  return left;
}

void Ast::AstNode::setLeftChild(AstNode *left)
{
  if (left != nullptr)
    left->parent = this;
  this->left = left;
}

Ast::AstNode* Ast::AstNode::getRightChild()
{
  return left;
}

void Ast::AstNode::setRightChild(AstNode *right)
{
  if (right != nullptr)
    right->parent = this;
  this->right = right;
}