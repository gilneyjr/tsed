#include "end_nodename_state.hpp"
#include "invalid_character_exception.hpp"

Nodename::EndNodenameState::EndNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) 
{
  machine->finish();
}

Nodename::EndNodenameState::~EndNodenameState() {}

Nodename::NodenameState* Nodename::EndNodenameState::run() 
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    return this;

  throw Exceptions::InvalidCharacterException(x);
}
