#include "search-expression.hpp"

Transduction::Search::SearchExpression::SearchExpression(
  const Nodename::NodenameInfoSet& definitions,
  const Nodename::NodenameInfoSet& references
) : definitions(definitions), references(references) {}

const Nodename::NodenameInfoSet& Transduction::Search::SearchExpression::getDefinitions() const
{
  return definitions;
}

const Nodename::NodenameInfoSet& Transduction::Search::SearchExpression::getReferences() const
{
  return references;
}