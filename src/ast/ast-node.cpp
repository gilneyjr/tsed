#include "ast-node.hpp"

Ast::AstNode::AstNode(
  AstNode* parent,
  AstNode* left,
  AstNode* right,
  Nodename::NodenameInfo* info
) : parent(parent), left(left), right(right), type(AstNodeType::Leaf), data(info)
{
  if (left != nullptr)
    left->parent = this;
  if (right != nullptr)
    right->parent = this;
}

Ast::AstNode::AstNode(
  AstNode* parent,
  AstNode* left,
  AstNode* right,
  std::string &operation,
  Nodename::NodenameInfoSet& definitions,
  Nodename::NodenameInfoSet& references
) : parent(parent), left(left), right(right), type(AstNodeType::Internal), data(operation, definitions, references) {}

Ast::AstNode::~AstNode()
{
  // TODO: if this is a leaf, it needs to delete the nodenameInfos
  delete left;
  delete right;
}

Ast::AstNode* Ast::AstNode::getLeft()
{
  return left;
}

void Ast::AstNode::setLeft(AstNode *left)
{
  if (left != nullptr)
    left->parent = this;
  this->left = left;
}

Ast::AstNode* Ast::AstNode::getRight()
{
  return right;
}

void Ast::AstNode::setRight(AstNode *right)
{
  if (right != nullptr)
    right->parent = this;
  this->right = right;
}

Ast::AstNode* Ast::AstNode::getParent()
{
  return parent;
}

bool Ast::AstNode::isLeaf()
{
  return type == AstNodeType::Leaf;
}

bool Ast::AstNode::isInternal()
{
  return type == AstNodeType::Internal;
}

std::ostream& Ast::operator<<(std::ostream& os, Ast::AstNode& node)
{
  os << "{";

  if (node.isLeaf())
    os << "\"root\":\"" << node.data.leaf.nodenameInfo->regex << "\",";
  else
    os << "\"root\":\"" << node.data.internal.operation << "\",";
  
  if (node.left)
    os << "\"left\":" << *node.left << ",";
  else
    os << "\"left\":null,";

  if (node.right)
    os << "\"right\":" << *node.right;
  else
    os << "\"right\":null";

  os << "}";
  return os;
}