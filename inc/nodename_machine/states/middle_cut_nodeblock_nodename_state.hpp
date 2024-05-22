#ifndef MIDDLE_CUT_NODEBLOCK_NODENAME_STATE_HPP
#define MIDDLE_CUT_NODEBLOCK_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class MiddleCutNodeblockNodenameState: public NodenameState
  {
    public:
    MiddleCutNodeblockNodenameState(NodenameMachine*);
    ~MiddleCutNodeblockNodenameState();
    virtual NodenameState* run();
  };
}

#endif
