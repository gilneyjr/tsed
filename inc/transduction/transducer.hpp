#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include "search-match-context.hpp"
#include "syntax-tree.hpp"
#include "transduction-rule.hpp"
#include "transversal-strategy.hpp"

namespace Transduction
{
  class Transducer
  {
  protected:
    TransversalStrategy* transversalStrategy;
    // void replaceMainMatch(Transduction::NodenameMatch &nodenameMatch, );

    // void replace(SymbolTable)

  public:
    Transducer(TransversalStrategy *transversalStrategy);
    ~Transducer();
    void transduce(TransductionRule*, SyntaxTree*);
  };
}

#endif
