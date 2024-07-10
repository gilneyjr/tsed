#include "end_nodename_state.hpp"
#include "invalid_character_exception.hpp"
#include "right_nodeblock_nodename_state.hpp"
#include "nodeblock_machine.hpp"

Nodename::RightNodeblockNodenameState::RightNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::RightNodeblockNodenameState::~RightNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::RightNodeblockNodenameState::run()
{
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input);
  auto nodeblockResult = nodeblockMachine->run();
  delete nodeblockMachine;

  if (nodeblockResult.regex.length() > 0)
    this->machine->setFreeOfContext(false);
  this->machine->incorporateFrom(nodeblockResult);

  char x;
  this->input >> x;
  
  if (this->input.eof())
    return new EndNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
