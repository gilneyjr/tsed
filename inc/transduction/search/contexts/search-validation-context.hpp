#ifndef SEARCH_VALIDATION_CONTEXT_HPP
#define SEARCH_VALIDATION_CONTEXT_HPP

#include <string>
#include <vector>
#include "nodename-info.hpp"

namespace Transduction::Search::Contexts
{
  struct SearchValidationContext
  {
    bool leftIsEndMarker;
    Nodename::NodenameInfoSet definitions;
    Nodename::NodenameInfoSet references;

    std::vector<std::string> errors;
    std::vector<std::string> warnings;
  };
}

#endif