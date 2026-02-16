#ifndef RESTRICTION_EXPRESSION_FACTORY_HPP
#define RESTRICTION_EXPRESSION_FACTORY_HPP

#include <string>
#include "restriction-expression.hpp"
#include "search-expression.hpp"

namespace Transduction::Search
{
  class RestrictionExpressionFactory
  {
  public:
    static RestrictionExpression* create(const std::string&, SearchExpression*);
  };
}

#endif
