#ifndef REPLACEMENT_TREE_HPP
#define REPLACEMENT_TREE_HPP

#include <string>
#include <vector>

namespace Transduction::Replacement
{
  class ReplacementTree;
  typedef std::vector<ReplacementTree*> TreeSequence;

  class ReplacementTree
  {
  public:
    virtual ~ReplacementTree() = default;
    virtual const TreeSequence* getChildren() const = 0;
    virtual const std::string& getTag() const = 0;
  };
}

#endif
