#include "replacement-validation-context.hpp"

Transduction::Replacement::Contexts::ReplacementValidationContext::ReplacementValidationContext(
  Nodename::NodenameInfoSet &searchDefinitions
) : searchDefinitions(searchDefinitions) {}