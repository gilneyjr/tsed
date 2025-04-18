#include "post-order-syntax-tree-iterator-strategy.hpp"

Transduction::SyntaxTree*
Transduction::PostOrderSyntaxTreeIteratorStrategy::start(SyntaxTree* root)
{
  if (root != nullptr)
    while (root->firstChild != nullptr)
      root = root->firstChild;
  return root;
}

Transduction::SyntaxTree*
Transduction::PostOrderSyntaxTreeIteratorStrategy::next(SyntaxTree* current)
{
  if (current == nullptr)
    return current;
  
  if (current->rightSibling)
  {
    current = current->rightSibling;
    while (current->firstChild)
      current = current->firstChild;
  }
  else
  {
    current = current->parent;
  }
  
  return current;
}