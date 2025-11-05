#ifndef SEARCH_EXPRESSION_HPP
#define SEARCH_EXPRESSION_HPP

#include "nodename-info.hpp"
#include "symbol-table.hpp"
#include "syntax-tree.hpp"

namespace Transduction::Search
{
  class SearchExpression
  {
  protected:
    Nodename::NodenameInfoSet definitions;
    Nodename::NodenameInfoSet references;
  public:
    SearchExpression() = default;
    SearchExpression(const Nodename::NodenameInfoSet&, const Nodename::NodenameInfoSet&);
    virtual ~SearchExpression() = default;
    virtual bool match(SyntaxTree*, SymbolTable&) = 0;
    const Nodename::NodenameInfoSet& getDefinitions() const;
    const Nodename::NodenameInfoSet& getReferences() const;
  };
}

#endif
