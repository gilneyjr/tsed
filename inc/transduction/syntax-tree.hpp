#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <string>

namespace Transduction
{
  class SyntaxTree
  {
  public:
    // TODO: turn some attributes to protected
    std::string tag;
    SyntaxTree* parent;
    SyntaxTree* firstChild;
    SyntaxTree* rightSibling;

    SyntaxTree(const std::string&, SyntaxTree*);
    ~SyntaxTree();
    void addChild(SyntaxTree*);

    class PreOrderIterator
    {
    public:
      // Types for compatibility with standard iterators
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = SyntaxTree;
      using pointer = SyntaxTree*;
      using reference = SyntaxTree&;

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