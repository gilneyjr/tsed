#include "replacement-leaf-node.hpp"

Transduction::Replacement::ReplacementLeafNode::ReplacementLeafNode(
  std::string &tag, Nodename::Placeholder placeholder, unsigned int placeholderNumber
) : tag(tag), placeholder(placeholder), placeholderNumber(placeholderNumber) {}

const std::string&
Transduction::Replacement::ReplacementLeafNode::getTag() const
{
  return tag;
}

const Transduction::Replacement::TreeSequence*
Transduction::Replacement::ReplacementLeafNode::getChildren() const
{
  return nullptr;
}

Nodename::Placeholder Transduction::Replacement::ReplacementLeafNode::getPlaceholder() const
{
  return placeholder;
}

unsigned int Transduction::Replacement::ReplacementLeafNode::getPlaceholderNumber() const
{
  return placeholderNumber;
}
