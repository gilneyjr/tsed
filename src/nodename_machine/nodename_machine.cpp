#include "nodename_machine.hpp"
#include "begin_nodename_state.hpp"

Nodename::NodenameMachine::NodenameMachine(std::istream& input, std::ostream& output)
  : input(input), output(output)
{
  this->state = new Nodename::BeginNodenameState(this);
  this->finished = false;
}

Nodename::NodenameMachine::~NodenameMachine() 
{
  delete this->state;
}

void Nodename::NodenameMachine::finish()
{
  this->finished = true;
}

void Nodename::NodenameMachine::run() 
{
  while (!this->finished && this->state != nullptr) 
  {
    NodenameState* nextState = this->state->run();
    if (this->state != nullptr && this->state != nextState) 
    {
      delete this->state;
      this->state = nextState;
    }
  }
}

std::istream& Nodename::NodenameMachine::getInputStream() 
{
  return this->input;
}

std::ostream& Nodename::NodenameMachine::getOutputStream()
{
  return this->output;
}