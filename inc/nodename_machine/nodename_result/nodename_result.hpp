#ifndef NODENAME_RESULT_HPP
#define NODENAME_RESULT_HPP

#include <string>

#include "def_or_ref.hpp"
#include "nodename_result_type.hpp"
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
    int placeholderNumber = 0;
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

    NodenameInfo(const NodenameInfo& other)
      : type(other.type),
        placeholder(other.placeholder),
        placeholderNumber(other.placeholderNumber),
        undetermined(other.undetermined),
        freeOfContext(other.freeOfContext),
        defOrRef(other.defOrRef),
        regex(other.regex),
        validAsLNodename(other.validAsLNodename),
        validAsRNodename(other.validAsRNodename) {}
  };
}

#endif
