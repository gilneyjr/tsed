#ifndef SEARCH_MATCH_CONTEXT_HPP
#define SEARCH_MATCH_CONTEXT_HPP

#include "symbol-table.hpp"
#include "syntax-tree.hpp"

namespace Transduction::Search::Contexts
{
  struct SearchMatchContext
  {
    SyntaxTree *current;
    SymbolTable *symbolTable;
    bool matchedIsEndMarker;
    SyntaxTree *matched;

    SearchMatchContext() = default;
    SearchMatchContext(const SearchMatchContext &other) = default;
    // TODO: Move matched to second parameter
    SearchMatchContext(
      SyntaxTree *current, SymbolTable *symbolTable,
      bool matchedIsEndMarker = false, SyntaxTree *matched = nullptr
    );
  };
}

#endif