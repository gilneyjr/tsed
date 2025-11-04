#ifndef REPLACEMENT_LEAF_NODE_HPP
#define REPLACEMENT_LEAF_NODE_HPP

#include "nodename_info.hpp"
#include "placeholder.hpp"
#include "replacement-tree.hpp"

namespace Transduction::Replacement
{
  class ReplacementLeafNode : public ReplacementTree
  {
  private:
    std::string tag;
    Nodename::Placeholder placeholder;
    unsigned int placeholderNumber;
  public:
    ReplacementLeafNode(std::string&, Nodename::Placeholder, unsigned int);
    ~ReplacementLeafNode() = default;
    const TreeSequence* getChildren() const;
    const std::string& getTag() const;
    Nodename::Placeholder getPlaceholder() const;
    unsigned int getPlaceholderNumber() const;
  };
}

#endif
