#include "begin-nodename-state.hpp"
#include "left-nodeblock-nodename-state.hpp"

Nodename::BeginNodenameState::BeginNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::BeginNodenameState::~BeginNodenameState() {}

Nodename::NodenameState* Nodename::BeginNodenameState::run()
{
  return new LeftNodeblockNodenameState(this->machine);
}
