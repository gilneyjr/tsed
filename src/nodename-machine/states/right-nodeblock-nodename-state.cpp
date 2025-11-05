#include "end-nodename-state.hpp"
#include "invalid-character-exception.hpp"
#include "right-nodeblock-nodename-state.hpp"
#include "nodeblock-machine.hpp"

Nodename::RightNodeblockNodenameState::RightNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::RightNodeblockNodenameState::~RightNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::RightNodeblockNodenameState::run()
{
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input);
  auto nodeblockResult = nodeblockMachine->run();
  delete nodeblockMachine;

  if (nodeblockResult.regex.length() > 2) // it's 2 because the empty regex is "()"
    this->machine->setFreeOfContext(false);
  this->machine->incorporateFrom(nodeblockResult);

  char x;
  this->input >> x;
  
  if (this->input.eof())
    return new EndNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
