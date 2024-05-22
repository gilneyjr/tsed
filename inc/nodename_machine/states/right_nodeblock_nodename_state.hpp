#ifndef RIGHT_NODEBLOCK_NODENAME_STATE_HPP
#define RIGHT_NODEBLOCK_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class RightNodeblockNodenameState: public NodenameState
  {
    public:
    RightNodeblockNodenameState(NodenameMachine*);
    ~RightNodeblockNodenameState();
    virtual NodenameState* run();
  };
}

#endif
