#include "begin_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"

Nodename::Nodeblock::BeginNodeblockState::BeginNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::BeginNodeblockState::~BeginNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::BeginNodeblockState::run()
{
  this->machine->appendToOutput('(');
  return new NormalNodeblockState(this->machine);
}
