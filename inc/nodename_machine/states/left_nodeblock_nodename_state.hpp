#ifndef LEFT_NODEBLOCK_NODENAME_STATE_HPP
#define LEFT_NODEBLOCK_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class LeftNodeblockNodenameState: public NodenameState
  {
    public:
    LeftNodeblockNodenameState(NodenameMachine*);
    ~LeftNodeblockNodenameState();
    virtual NodenameState* run();
  };
}

#endif
