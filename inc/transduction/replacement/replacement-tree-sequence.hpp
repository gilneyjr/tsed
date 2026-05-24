#ifndef REPLACEMENT_TREE_SEQUENCE_HPP
#define REPLACEMENT_TREE_SEQUENCE_HPP

#include "syntax-tree.hpp"
#include "nodename-match.hpp"

#include <initializer_list>
#include <vector>
#include <map>

namespace Transduction::Replacement
{
  class ReplacementTree;

  class ReplacementTreeSequence
  {
  private:
    std::vector<ReplacementTree*> replacementTrees;
  public:
    ReplacementTreeSequence() = default;
    ReplacementTreeSequence(std::vector<ReplacementTree*> &replacementTrees);
    ReplacementTreeSequence(std::initializer_list<ReplacementTree*> replacementTrees);
    ~ReplacementTreeSequence();
    void addTree(ReplacementTree *replacementTree);
    std::vector<ReplacementTree*>::iterator begin();
    std::vector<ReplacementTree*>::iterator end();
    bool empty() const;
    std::vector<Transduction::SyntaxTree*> generateSyntaxTrees(
      const std::map<unsigned int, Transduction::NodenameMatch> &matches) const;
  };
}

#endif
