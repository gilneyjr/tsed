#include "doctest.h"
#include "pre-order-syntax-tree-iterator-strategy.hpp"
#include "single-match-traversal-behavior.hpp"
#include "symbol-table.hpp"
#include "traversal-behavior-test-utils.hpp"

#include <vector>

TEST_SUITE("Single-match traversal behavior")
{
  TEST_CASE("Traversal remains complete although notify match on an empty tree")
  {
    auto order = new Transduction::PreOrderSyntaxTreeIteratorStrategy;
    auto behavior = new Transduction::SingleMatchTraversalBehavior(order);

    auto tree = createEmptyTree();
    behavior->start(tree);

    Transduction::SymbolTable symbolTable;
    behavior->notifyMatch(symbolTable);

    std::vector<Transduction::SyntaxTree*> replacedTrees;
    behavior->notifyReplacement(replacedTrees);

    CHECK(!behavior->hasNext());
    
    delete behavior;
  }

  TEST_CASE("Traversal stops after a match on any node")
  {
    auto tree = createRepresentativeTree();
    auto it = new Transduction::PreOrderSyntaxTreeIteratorStrategy;
    auto node = it->start(tree);

    while (node != nullptr)
    {
      auto order = new Transduction::PreOrderSyntaxTreeIteratorStrategy;
      auto behavior = new Transduction::SingleMatchTraversalBehavior(order);

      behavior->start(tree);
      CHECK(behavior->hasNext());

      Transduction::SymbolTable symbolTable;
      behavior->notifyMatch(symbolTable);

      std::vector<Transduction::SyntaxTree*> replacedTrees;
      behavior->notifyReplacement(replacedTrees);

      CHECK(!behavior->hasNext());
      
      delete behavior;

      node = it->next(node);
    }

    delete it;
  }
}
