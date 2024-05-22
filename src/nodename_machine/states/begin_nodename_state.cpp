#include "begin_nodename_state.hpp"
#include "left_nodeblock_nodename_state.hpp"

Nodename::BeginNodenameState::BeginNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::BeginNodenameState::~BeginNodenameState() {}

Nodename::NodenameState* Nodename::BeginNodenameState::run()
{
  return new LeftNodeblockNodenameState(this->machine);
}
