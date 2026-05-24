#ifndef REPLACEMENT_TREE_HPP
#define REPLACEMENT_TREE_HPP

#include "nodename-match.hpp"
#include "replacement-validation-context.hpp"
#include "placeholder.hpp"
#include <string>
#include <vector>

namespace Transduction::Replacement
{
  class ReplacementTreeSequence;
  class ReplacementTree
  {
  private:
    std::string tag;
    Nodename::Placeholder placeholder;
    unsigned int placeholderNumber;
    ReplacementTreeSequence *children;
  public:
    ReplacementTree(
      const std::string &tag,
      Nodename::Placeholder placeholder = Nodename::Placeholder::NONE,
      unsigned int placeholderNumber = 0);
    ReplacementTree(const std::string &tag, ReplacementTreeSequence *children);
    ~ReplacementTree();
    const std::string& getTag() const;
    Nodename::Placeholder getPlaceholder() const;
    unsigned int getPlaceholderNumber() const;
    const ReplacementTreeSequence* getChildren() const;
    void setChildren(ReplacementTreeSequence *children);
    void validate(Contexts::ReplacementValidationContext &context) const;
    std::vector<SyntaxTree*> generateSyntaxTrees(
      const std::map<unsigned int, Transduction::NodenameMatch> &matches) const;
  };
}

#endif
