#ifndef NODENAME_INFO_TYPE_HPP
#define NODENAME_INFO_TYPE_HPP

namespace Nodename
{
  enum class NodenameInfoType 
  {
    SIMPLE_NODE = 0,
    NODE_PLACEHOLDER = 1,
    SUBTREE_RANGE_PLACEHOLDER = 2,
    END_MARKER = 3
  };
}

#endif
