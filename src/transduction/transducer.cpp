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

  SyntaxTree* initialEndMarker = tree->getParent();
  transversalStrategy->start(initialEndMarker);
  while (transversalStrategy->hasNext())
  {
    SyntaxTree* current = transversalStrategy->next();
    SymbolTable symbolTable;
    Transduction::Search::Contexts::SearchMatchContext context(current, &symbolTable);
    if (rule->search->match(context))
    {
      // TODO: remove these cout's later
      std::cout << "MATCHED!" << std::endl;

      std::cout << "SEARCH PRIMARY:" << std::endl;
      std::cout << "\t" << *current << std::endl;

      std::cout << "MATCHES:" << std::endl;
      for (unsigned int i = 0u; i < 100; i++)
      {
        auto result = symbolTable.lookup(i);
        if (result.first)
        {
          std::cout << "Match " << i << ":" << std::endl;
          if (result.second.trees.empty())
            std::cout << "\t[EMPTY]" << std::endl;
          else
            for (auto tree : result.second.trees)
              std::cout << "\t" << *tree << std::endl;
        }
      }
      this->transversalStrategy->notifyTransduction();
      // TODO: apply replacement expression here
    }
  }
}
