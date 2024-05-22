#include "end_nodename_state.hpp"

Nodename::EndNodenameState::EndNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) 
{
  machine->finish();
}

Nodename::EndNodenameState::~EndNodenameState() {}

Nodename::NodenameState* Nodename::EndNodenameState::run() 
{
  return this;
}
