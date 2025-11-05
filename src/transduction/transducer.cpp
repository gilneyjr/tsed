#include <climits>
#include <iostream> // TODO: Remove it later
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "transducer.hpp"

Transduction::Transducer::Transducer(TransversalStrategy* transversalStrategy)
  : transversalStrategy(transversalStrategy) {}

Transduction::Transducer::~Transducer()
{
  if (this->transversalStrategy)
    delete this->transversalStrategy;
}

void Transduction::Transducer::apply(TransductionRule *rule, SyntaxTree* tree)
{
  if (rule == nullptr || tree == nullptr)
    return;

  transversalStrategy->start(tree);
  while (transversalStrategy->hasNext())
  {
    SyntaxTree* current = transversalStrategy->next();
    SymbolTable symbolTable;
    if (rule->search->match(current, symbolTable))
    {
      std::cout << *current << std::endl;
      this->transversalStrategy->notifyTransduction();
      // TODO: apply replacement expression here
    }
  }
}
