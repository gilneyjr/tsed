#include <stdexcept>
#include "syntax-tree-iterator.hpp"

Transduction::SyntaxTreeIterator::SyntaxTreeIterator()
{
  this->current = nullptr;
  this->strategy = nullptr;
}

Transduction::SyntaxTreeIterator::SyntaxTreeIterator(SyntaxTree* root, SyntaxTreeIteratorStrategy* strategy)
  : strategy(strategy)
{
  if (strategy == nullptr)
    throw std::runtime_error("SyntaxTreeIterator requires a non-null SyntaxTreeIteratorStrategy. Pass a valid strategy to the constructor."); // TODO: change this later
  this->current = strategy->start(root);
}

Transduction::SyntaxTree&
Transduction::SyntaxTreeIterator::operator*() const
{
  return *current;
}

Transduction::SyntaxTree*
Transduction::SyntaxTreeIterator::operator->() const
{
  return current;
}

bool Transduction::SyntaxTreeIterator::operator==(const SyntaxTreeIterator& other) const
{
  return current == other.current;
}

bool Transduction::SyntaxTreeIterator::operator!=(const SyntaxTreeIterator& other) const
{
  return current != other.current;
}

Transduction::SyntaxTreeIterator& Transduction::SyntaxTreeIterator::operator++()
{
  this->current = this->strategy->next(this->current);
  return *this;
}

Transduction::SyntaxTreeIterator Transduction::SyntaxTreeIterator::operator++(int)
{
  SyntaxTreeIterator temp = *this;
  ++(*this);
  return temp;
}