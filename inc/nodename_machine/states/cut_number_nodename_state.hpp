#ifndef CUT_NUMBER_NODENAME_STATE_HPP
#define CUT_NUMBER_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class CutNumberNodenameState: public NodenameState
  {
  public:
    CutNumberNodenameState(NodenameMachine*);
    ~CutNumberNodenameState();
    virtual NodenameState* run();
  };
}

#endif
