#ifndef NODENAME_INFO_HPP
#define NODENAME_INFO_HPP

#include <string>
#include <map>

#include "def-or-ref.hpp"
#include "nodename-info-type.hpp"
#include "placeholder.hpp"

namespace Nodename
{
  enum class NodenameInfoType;
  enum class Placeholder;
  enum class DefOrRef;

  struct NodenameInfo
  {
    NodenameInfoType type = NodenameInfoType::SIMPLE_NODE;
    Placeholder placeholder = Placeholder::NONE;
    unsigned int placeholderNumber = 0;
    bool undetermined = false; // true, when nodename has ANY, WILDCARD or REGEX inside it; false, otherwise.
    bool freeOfContext = true; // true, when nodename doesn't have specified left or right contexts; false, otherwise.
    DefOrRef defOrRef = DefOrRef::NONE;
    std::string regex = "";

    NodenameInfo();
    NodenameInfo(const NodenameInfo& other) = default;

    static NodenameInfo* createSubtreeRangeInstance(Placeholder placeholder, unsigned int placeholderNumber);
    static NodenameInfo* createEndMarkerInstance();

    static const unsigned int MAIN_PLACEHOLDER_NUMBER;
  };

  typedef std::map<unsigned int, NodenameInfo*> NodenameInfoSet;
}

#endif
