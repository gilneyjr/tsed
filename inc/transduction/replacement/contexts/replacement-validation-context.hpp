#ifndef REPLACEMENT_VALIDATION_CONTEXT_HPP
#define REPLACEMENT_VALIDATION_CONTEXT_HPP

#include "nodename-info.hpp"
#include <string>
#include <vector>

namespace Transduction::Replacement::Contexts
{
  struct ReplacementValidationContext
  {
    ReplacementValidationContext(Nodename::NodenameInfoSet&);

    Nodename::NodenameInfoSet &searchDefinitions;
    Nodename::NodenameInfoSet references;

    std::vector<std::string> errors;
    std::vector<std::string> warnings;
  };
}

#endif
