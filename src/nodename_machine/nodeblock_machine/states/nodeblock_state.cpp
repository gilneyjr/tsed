#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockState::NodeblockState(
  Nodename::Nodeblock::NodeblockMachine *machine): 
    machine(machine), 
    in(*(machine->getInputStream())),
    out(*(machine->getOutputStream())) {}
    
Nodename::Nodeblock::NodeblockState::~NodeblockState() {}