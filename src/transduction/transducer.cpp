#include <climits>
#include <iostream> // TODO: Remove it later
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "transducer.hpp"

Transduction::Transducer::Transducer(TraversalBehavior* traversalBehavior)
  : traversalBehavior(traversalBehavior) {}

Transduction::Transducer::~Transducer()
{
  if (this->traversalBehavior)
    delete this->traversalBehavior;
}

void Transduction::Transducer::transduce(TransductionRule *rule, SyntaxTree* tree)
{
  if (rule == nullptr || tree == nullptr)
    return;

  SyntaxTree* initialEndMarker = tree->getParent();
  traversalBehavior->start(initialEndMarker);
  while (traversalBehavior->hasNext())
  {
    SyntaxTree* current = traversalBehavior->next();
    SymbolTable symbolTable;
    Transduction::Search::Contexts::SearchMatchContext searchContext(current, &symbolTable);
    if (rule->getSearchExpression()->match(searchContext))
    {
      // TODO: remove these cout's later
      std::cout << "MATCHED!" << std::endl;

      // std::cout << "SEARCH PRIMARY:" << std::endl;
      // std::cout << "\t" << *current << std::endl;

      this->traversalBehavior->notifyTransduction();
      
      // TODO: apply replacement expression here
      // auto generatedTrees = rule->getReplacementExpression()->generateTrees(symbolTable);

      rule->getReplacementExpression()->replace(tree, symbolTable);

      // auto mainMatch = symbolTable
      //   .lookup(Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER)
      //   .second;

      // if (generatedTrees.size() > 1 && mainMatch.matchedIsRoot())
      // {
      //   // TODO: Correct/Improve this error message
      //   throw "Error in replacement: the root main placeholder cannot be replaced with a tree range.";
      // }

      // replaceMainMatch(mainMatch, generatedTrees);
    }
  }
}
