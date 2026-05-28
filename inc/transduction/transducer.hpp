#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include "search-match-context.hpp"
#include "syntax-tree.hpp"
#include "transduction-rule.hpp"
#include "traversal-behavior.hpp"

namespace Transduction
{
  class Transducer
  {
  protected:
    TraversalBehavior* traversalBehavior;
    // void replaceMainMatch(Transduction::NodenameMatch &nodenameMatch, );

    // void replace(SymbolTable)

  public:
    Transducer(TraversalBehavior *traversalBehavior);
    ~Transducer();
    void transduce(TransductionRule*, SyntaxTree*);
  };
}

#endif
