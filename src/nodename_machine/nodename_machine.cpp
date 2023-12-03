#include "nodename_machine.hpp"
#include "begin_nodename_state.hpp"

Nodename::NodenameMachine::NodenameMachine() {
  this->state = new Nodename::BeginNodenameState(this);
  this->finished = false;
}

Nodename::NodenameMachine::~NodenameMachine() {
  delete this->state;
}

void Nodename::NodenameMachine::changeState(Nodename::NodenameState *state) {
  delete this->state;
  this->state = state;
}

void Nodename::NodenameMachine::finish() {
  this->finished = true;
}

void Nodename::NodenameMachine::run() {
  while (!this->finished)
    this->state->run();
}