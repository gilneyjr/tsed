#ifndef NODENAME_INFO_HPP
#define NODENAME_INFO_HPP

#include <string>
#include <set>

#include "def_or_ref.hpp"
#include "nodename_info_type.hpp"
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
    unsigned int placeholderNumber = -1;
    bool undetermined = false; // true, when nodename has ANY, WILDCARD or REGEX inside it; false, otherwise.
    bool freeOfContext = true; // true, when nodename doesn't have specified left or right contexts; false, otherwise.
    DefOrRef defOrRef = DefOrRef::NONE; // The placeholder is a definition, a reference or neither of them.
    std::string regex = "";

    // TODO: Verify if the following attributes need to be in this class
    bool validAsLNodename = true; // Depends on context 
    bool validAsRNodename = true; // !undetermined && freeOfContext && defOrRef != DEFINITION

    NodenameInfo()
      : type(NodenameInfoType::SIMPLE_NODE),
        placeholder(Placeholder::NONE),
        placeholderNumber(0),
        undetermined(false),
        freeOfContext(true),
        defOrRef(DefOrRef::NONE),
        regex(""),
        validAsLNodename(true),
        validAsRNodename(true) {}

    NodenameInfo(const NodenameInfo& other) = default;

    // TODO: move to .cpp
    static NodenameInfo* newSubtreeRangeInstance(Placeholder placeholder, unsigned int placeholderNumber)
    {
      auto info = new NodenameInfo();

      info->type = NodenameInfoType::SUBTREE_RANGE_PLACEHOLDER;
      info->placeholder = placeholder;
      info->placeholderNumber = placeholderNumber;
      info->undetermined = false;
      info->freeOfContext = true;
      info->defOrRef = DefOrRef::DEFINITION;
      info->regex = "";

      return info;
    }

    // TODO: move to .cpp
    static NodenameInfo* newEndMarkerInstance()
    {
      auto info = new NodenameInfo();

      info->type = NodenameInfoType::END_MARKER;
      info->placeholder = Placeholder::NONE;
      info->placeholderNumber = -1;
      info->undetermined = false;
      info->freeOfContext = true;
      info->defOrRef = DefOrRef::NONE;
      info->regex = "";

      return info;
    }
  };

  // TODO: move to a .cpp file
  struct NodenameInfoPointerComparator 
  {
    bool operator()(const NodenameInfo* left, const NodenameInfo* right) const
    {
      if (left == nullptr)
        return false;
      if (right == nullptr)
        return true;
      return left->placeholderNumber < right->placeholderNumber;
    }
  };

  typedef std::set<NodenameInfo*, NodenameInfoPointerComparator> NodenameInfoSet;
}

#endif
