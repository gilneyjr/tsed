#ifndef SYNTACTIC_TREE_HPP
#define SYNTACTIC_TREE_HPP

#include <string>

namespace Transduction
{
  class SyntacticTree
  {
  public:
    std::string tag;
    SyntacticTree* parent;
    SyntacticTree* firstChild;
    SyntacticTree* rightSibling;

    SyntacticTree(const std::string&, SyntacticTree*);
    ~SyntacticTree();
    void addChild(SyntacticTree*);

    class PreOrderIterator
    {
    public:
      // Types for compatibility with standard iterators
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = SyntacticTree;
      using pointer = SyntacticTree*;
      using reference = SyntacticTree&;

    private:
      pointer current;

    public:
      PreOrderIterator(pointer);
      reference operator*() const;
      pointer operator->() const;
      PreOrderIterator& operator++();
      PreOrderIterator operator++(int);
      bool operator==(const PreOrderIterator& other) const;
      bool operator!=(const PreOrderIterator& other) const;
    };
    
    PreOrderIterator begin();
    PreOrderIterator end();
  };
}

#endif