#include "post-order-syntax-tree-iterator-strategy.hpp"

Transduction::SyntaxTree*
Transduction::PostOrderSyntaxTreeIteratorStrategy::start(SyntaxTree* root)
{
  if (root != nullptr)
    while (root->getFirstChild() != nullptr)
      root = root->getFirstChild();
  return root;
}

Transduction::SyntaxTree*
Transduction::PostOrderSyntaxTreeIteratorStrategy::next(SyntaxTree* current)
{
  if (current == nullptr)
    return current;
  
  if (current->getRightSibling())
  {
    current = current->getRightSibling();
    while (current->getFirstChild())
      current = current->getFirstChild();
  }
  else
  {
    current = current->getParent();
  }
  
  return current;
}