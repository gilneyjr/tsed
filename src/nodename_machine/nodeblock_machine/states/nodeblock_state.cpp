#include "nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockState::NodeblockState(
  Nodename::Nodeblock::NodeblockMachine *machine): 
    machine(machine), 
    input(machine->getInputStream()) {}
    
Nodename::Nodeblock::NodeblockState::~NodeblockState() {}
