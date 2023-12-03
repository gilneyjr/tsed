#include "end_nodeblock_state.hpp"

Nodename::Nodeblock::EndNodeblockState::EndNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) 
{
  machine->finish();
}

Nodename::Nodeblock::EndNodeblockState::~EndNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::EndNodeblockState::run() 
{ 
  return this;
}