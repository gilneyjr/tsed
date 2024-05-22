#ifndef COPY_NUMBER_NODENAME_STATE_HPP
#define COPY_NUMBER_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class CopyNumberNodenameState: public NodenameState
  {
  public:
    CopyNumberNodenameState(NodenameMachine*);
    ~CopyNumberNodenameState();
    virtual NodenameState* run();
  };
}

#endif
