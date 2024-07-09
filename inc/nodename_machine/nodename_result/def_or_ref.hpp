#ifndef NODENAME_RESULT_TYPE
#define NODENAME_RESULT_TYPE

namespace Nodename::NodenameResult
{
  enum class DefOrRef {
    NONE = 0,
    DEFINITION = 1,
    REFERENCE = 2
  };
}

#endif
