#ifndef TRAVERSAL_BEHAVIOR_TYPE_HPP
#define TRAVERSAL_BEHAVIOR_TYPE_HPP

namespace Transduction
{
  enum class TraversalBehaviorType
  {
    FOLLOW_REPLACEMENT = 1,
    SKIP_MODIFIED = 2,
    FORCE_RECURSION = 3,
    SINGLE_MATCH = 4,
    ROOT_RESTART = 5
  };
}

#endif
