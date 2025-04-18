#ifndef SYNTAX_TREE_ITERATOR_HPP
#define SYNTAX_TREE_ITERATOR_HPP

#include "syntax-tree.hpp"
#include "syntax-tree-iterator-strategy.hpp"

namespace Transduction
{
  class SyntaxTreeIterator
  {
  protected:
    SyntaxTreeIteratorStrategy* strategy;
    SyntaxTree* current;
  public:
    SyntaxTreeIterator();
    SyntaxTreeIterator(SyntaxTree*, SyntaxTreeIteratorStrategy*);
    SyntaxTree& operator*() const;
    SyntaxTree* operator->() const;
    bool operator==(const SyntaxTreeIterator& other) const;
    bool operator!=(const SyntaxTreeIterator& other) const;
    SyntaxTreeIterator& operator++();
    SyntaxTreeIterator operator++(int);
  };
}

#endif
