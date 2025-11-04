#ifndef REPLACEMENT_INTERNAL_NODE_HPP
#define REPLACEMENT_INTERNAL_NODE_HPP

#include "replacement-tree.hpp"

namespace Transduction::Replacement
{
  class ReplacementInternalNode: public ReplacementTree
  {
  private:
    std::string tag;
    TreeSequence *children;
  public:
    ReplacementInternalNode(const std::string&, TreeSequence*);
    ~ReplacementInternalNode();
    const TreeSequence* getChildren() const;
    const std::string& getTag() const;
  };
}

#endif
