#include "search-match-context.hpp"

Transduction::Search::Contexts::SearchMatchContext::SearchMatchContext(
  SyntaxTree *matched, SymbolTable *symbolTable, bool matchedIsEndMarker
) : matched(matched), symbolTable(symbolTable), matchedIsEndMarker(matchedIsEndMarker) {}