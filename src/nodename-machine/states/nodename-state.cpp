#include "nodename-state.hpp"

Nodename::NodenameState::NodenameState(
  Nodename::NodenameMachine *machine): 
    machine(machine), 
    input(machine->getInputStream()) {}

Nodename::NodenameState::~NodenameState() {}
