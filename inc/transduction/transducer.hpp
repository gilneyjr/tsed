#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include "syntax-tree.hpp"
#include "transduction-rule.hpp"
#include "transversal-strategy.hpp"

namespace Transduction
{
  class Transducer
  {
  protected:
    TransversalStrategy* transversalStrategy;

  public:
    Transducer(TransversalStrategy*);
    ~Transducer();
    void apply(TransductionRule*, SyntaxTree*);
  };
}

#endif
