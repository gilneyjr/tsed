#ifndef NODENAME_EXPRESSION_HPP
#define NODENAME_EXPRESSION_HPP

#include "nodename-info.hpp"
#include "search-match-context.hpp"
#include "search-validation-context.hpp"

namespace Transduction::Search
{
  class NodenameExpression
  {
  private:
    Nodename::NodenameInfo *nodenameInfo;
  public:
    NodenameExpression(Nodename::NodenameInfo*);
    ~NodenameExpression();
    bool isEndMarker() const;
    bool match(Contexts::SearchMatchContext&) const;
    void validate(Contexts::SearchValidationContext&) const;
  };
}

#endif
