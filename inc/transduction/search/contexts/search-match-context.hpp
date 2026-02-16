#ifndef SEARCH_MATCH_CONTEXT_HPP
#define SEARCH_MATCH_CONTEXT_HPP

#include "symbol-table.hpp"
#include "syntax-tree.hpp"

namespace Transduction::Search::Contexts
{
  struct SearchMatchContext
  {
    SyntaxTree *matched;
    SymbolTable *symbolTable;
    bool matchedIsEndMarker;

    SearchMatchContext() = default;
    SearchMatchContext(SyntaxTree*, SymbolTable*, bool = false);
  };
}

#endif