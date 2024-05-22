#ifndef MIDDLE_COPY_NODEBLOCK_NODENAME_STATE_HPP
#define MIDDLE_COPY_NODEBLOCK_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class MiddleCopyNodeblockNodenameState: public NodenameState
  {
    public:
    MiddleCopyNodeblockNodenameState(NodenameMachine*);
    ~MiddleCopyNodeblockNodenameState();
    virtual NodenameState* run();
  };
}

#endif
