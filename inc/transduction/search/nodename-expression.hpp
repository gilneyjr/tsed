#ifndef NODENAME_EXPRESSION_HPP
#define NODENAME_EXPRESSION_HPP

#include "nodename-info.hpp"
#include "search-match-context.hpp"
#include "search-validation-context.hpp"
#include "subtree-range-direction.hpp"

namespace Transduction::Search
{
  class NodenameExpression
  {
  private:
    Nodename::NodenameInfo *nodenameInfo;
    bool matchEndMarker(Contexts::SearchMatchContext &context) const;
    bool matchSubtreeRange(Contexts::SearchMatchContext &context) const;
  public:
    NodenameExpression(Nodename::NodenameInfo *nodenameInfo);
    ~NodenameExpression();
    bool isEndMarker() const;
    bool isSubtreeRange() const;
    bool match(Contexts::SearchMatchContext &context) const;
    void validate(Contexts::SearchValidationContext &context) const;
    void print(int tab = 0);
  };
}

#endif
