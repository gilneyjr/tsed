#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <forward_list>
#include <map>
#include <utility>
#include "nodename-match.hpp"

namespace Transduction
{
  class SymbolTable
  {
  private:
    std::forward_list<std::map<unsigned int, NodenameMatch>> scopes;
  public:
    SymbolTable();
    void enterScope();
    void exitScope();
    void insert(const unsigned int, const NodenameMatch&);
    std::pair<bool, NodenameMatch> lookup(const unsigned int) const;
  };
}

#endif
