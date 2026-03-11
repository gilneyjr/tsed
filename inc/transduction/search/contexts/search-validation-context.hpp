#ifndef SEARCH_VALIDATION_CONTEXT_HPP
#define SEARCH_VALIDATION_CONTEXT_HPP

#include "nodename-info.hpp"
#include <string>
#include <vector>

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