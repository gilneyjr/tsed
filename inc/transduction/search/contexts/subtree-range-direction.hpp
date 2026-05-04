#ifndef SUBTREE_RANGE_DIRECTION
#define SUBTREE_RANGE_DIRECTION

namespace Transduction::Search::Contexts
{
  enum class SubtreeRangeDirection {
    NONE = 0,
    LEFT_SIBLINGS = 1,
    RIGHT_SIBLINGS = 2,
    CHILDREN = 3
  };
}

#endif
