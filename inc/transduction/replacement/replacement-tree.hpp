#ifndef REPLACEMENT_TREE_HPP
#define REPLACEMENT_TREE_HPP

#include "replacement-validation-context.hpp"
#include "placeholder.hpp"
#include <string>
#include <vector>

namespace Transduction::Replacement
{
  class ReplacementTree;
  typedef std::vector<ReplacementTree*> TreeSequence;

  class ReplacementTree
  {
  private:
    std::string tag;
    Nodename::Placeholder placeholder;
    unsigned int placeholderNumber;
    TreeSequence *children;
  public:
    ReplacementTree(const std::string&, Nodename::Placeholder = Nodename::Placeholder::NONE, unsigned int = 0);
    ReplacementTree(const std::string&, TreeSequence*);
    ~ReplacementTree();
    const std::string& getTag() const;
    Nodename::Placeholder getPlaceholder() const;
    unsigned int getPlaceholderNumber() const;
    const TreeSequence* getChildren() const;
    void setChildren(TreeSequence*);
    void validate(Contexts::ReplacementValidationContext&) const;
  };
}

#endif
