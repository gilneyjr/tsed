#ifndef MIDDLE_COPY_NODENAME_STATE_HPP
#define MIDDLE_COPY_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class MiddleCopyNodenameState: public NodenameState
  {
    public:
    MiddleCopyNodenameState(NodenameMachine*);
    ~MiddleCopyNodenameState();
    virtual NodenameState* run();
  };
}

#endif
