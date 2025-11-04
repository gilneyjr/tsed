#include "replacement-internal-node.hpp"

Transduction::Replacement::ReplacementInternalNode::ReplacementInternalNode(const std::string &tag, Transduction::Replacement::TreeSequence *children)
  : tag(tag), children(children) {}

Transduction::Replacement::ReplacementInternalNode::~ReplacementInternalNode()
{
  for (auto *child : *children)
    delete child;
  delete children;
}

const Transduction::Replacement::TreeSequence*
Transduction::Replacement::ReplacementInternalNode::getChildren() const
{
  return children;
}

const std::string& Transduction::Replacement::ReplacementInternalNode::getTag() const
{
  return tag;
}