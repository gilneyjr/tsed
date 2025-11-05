#include "invalid-character-exception.hpp"
#include "middle-copy-nodeblock-nodename-state.hpp"
#include "nodeblock-machine.hpp"
#include "right-nodeblock-nodename-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

Nodename::MiddleCopyNodeblockNodenameState::MiddleCopyNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::MiddleCopyNodeblockNodenameState::~MiddleCopyNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::MiddleCopyNodeblockNodenameState::run()
{
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input);
  auto nodeblockResult = nodeblockMachine->run();
  delete nodeblockMachine;


  if (nodeblockResult.regex.length() > 2) // 2 is an empty regex: "()"
    this->machine->setDefOrRef(DefOrRef::DEFINITION);
  else
    this->machine->setDefOrRef(DefOrRef::REFERENCE);
  this->machine->incorporateFrom(nodeblockResult);

  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == '}')
    return new RightNodeblockNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
