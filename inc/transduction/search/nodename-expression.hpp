#ifndef NODENAME_EXPRESSION_HPP
#define NODENAME_EXPRESSION_HPP

#include "nodename_info.hpp"
#include "search-expression.hpp"

namespace Transduction::Search
{
  class NodenameExpression : public SearchExpression
  {
  protected:
    Nodename::NodenameInfo *nodenameInfo;
  public:
    NodenameExpression(Nodename::NodenameInfo*);
    bool match(SyntaxTree*, SymbolTable&);
    bool isEndMarker();
    Nodename::NodenameInfo* getNodenameInfo();
  };
}

#endif
