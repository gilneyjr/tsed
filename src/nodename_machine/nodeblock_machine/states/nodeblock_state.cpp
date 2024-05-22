#include "nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockState::NodeblockState(
  Nodename::Nodeblock::NodeblockMachine *machine): 
    machine(machine), 
    input(machine->getInputStream()),
    output(machine->getOutputStream()) {}
    
Nodename::Nodeblock::NodeblockState::~NodeblockState() {}
