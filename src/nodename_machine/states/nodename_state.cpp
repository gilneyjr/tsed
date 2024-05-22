#include "nodename_state.hpp"

Nodename::NodenameState::NodenameState(
  Nodename::NodenameMachine *machine): 
    machine(machine), 
    input(machine->getInputStream()),
    output(machine->getOutputStream()) {}

Nodename::NodenameState::~NodenameState() {}
