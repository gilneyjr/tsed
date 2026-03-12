#include "nodename-info.hpp"
#include <cassert>

Nodename::NodenameInfo::NodenameInfo()
  : type(NodenameInfoType::SIMPLE_NODE),
    placeholder(Placeholder::NONE),
    placeholderNumber(0),
    undetermined(false),
    freeOfContext(true),
    defOrRef(DefOrRef::NONE),
    regex("") {}

Nodename::NodenameInfo* Nodename::NodenameInfo::createSubtreeRangeInstance(Placeholder placeholder, unsigned int placeholderNumber)
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

Nodename::NodenameInfo* Nodename::NodenameInfo::createEndMarkerInstance()
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

const unsigned int Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER = 0U;
