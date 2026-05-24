
#include "symbol-table.hpp"

Transduction::SymbolTable::SymbolTable()
{
  enterScope();
}

void Transduction::SymbolTable::enterScope()
{
  scopes.push_front({});
}

void Transduction::SymbolTable::exitScope()
{
  if (!scopes.empty())
    scopes.pop_front();
}

void Transduction::SymbolTable::insert(const unsigned int key, const NodenameMatch &match)
{
  scopes.front()[key] = match;
}

std::pair<bool, Transduction::NodenameMatch> Transduction::SymbolTable::lookup(const unsigned int key) const
{
  for (auto it = scopes.begin(); it != scopes.end(); ++it)
  {
    auto matchIt = it->find(key); 
    if (matchIt != it->end())
      return { true, matchIt->second };
  }

  return { false, {} };
}

std::map<unsigned int, Transduction::NodenameMatch> Transduction::SymbolTable::getAllMatches() const
{
  std::map<unsigned int, Transduction::NodenameMatch> matches;
  for (const auto &scope : scopes)
    matches.insert(scope.begin(), scope.end());
  return matches;
}
