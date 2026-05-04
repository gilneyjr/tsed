#include "search-match-context.hpp"

Transduction::Search::Contexts::SearchMatchContext::SearchMatchContext(
  SyntaxTree *current, SymbolTable *symbolTable,
  bool matchedIsEndMarker, SyntaxTree *matched,
  SubtreeRangeDirection subtreeRangeDirection
) : current(current), symbolTable(symbolTable)
  , matchedIsEndMarker(matchedIsEndMarker), matched(matched)
  , subtreeRangeDirection(subtreeRangeDirection) {}