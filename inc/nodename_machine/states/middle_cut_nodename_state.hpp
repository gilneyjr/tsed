#ifndef MIDDLE_CUT_NODENAME_STATE_HPP
#define MIDDLE_CUT_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class MiddleCutNodenameState: public NodenameState
  {
    public:
    MiddleCutNodenameState(NodenameMachine*);
    ~MiddleCutNodenameState();
    virtual NodenameState* run();
  };
}

#endif
