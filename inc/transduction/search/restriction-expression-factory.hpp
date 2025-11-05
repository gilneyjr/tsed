#ifndef RESTRICTION_EXPRESSION_FACTORY_HPP
#define RESTRICTION_EXPRESSION_FACTORY_HPP

#include <string>
#include "search-expression.hpp"

namespace Transduction::Search
{
  class RestrictionExpressionFactory
  {
  public:
    static SearchExpression* create(const std::string&, SearchExpression*);
  };
}

#endif
