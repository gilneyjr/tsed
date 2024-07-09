#ifndef NODENAME_RESULT_TYPE_HPP
#define NODENAME_RESULT_TYPE_HPP

namespace Nodename::NodenameResult
{
  enum class NodenameResultType 
  {
    SIMPLE_NODE = 0,
    NODE_PLACEHOLDER = 1,
    SUBTREE_RANGE_PLACEHOLDER = 2,
    END_MARKER = 3
  };
}

#endif
