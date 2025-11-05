#include "end-nodename-state.hpp"
#include "invalid-character-exception.hpp"
#include "left-nodeblock-nodename-state.hpp"
#include "middle-copy-nodename-state.hpp"
#include "middle-cut-nodename-state.hpp"
#include "nodeblock-machine.hpp"

Nodename::LeftNodeblockNodenameState::LeftNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::LeftNodeblockNodenameState::~LeftNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::LeftNodeblockNodenameState::run()
{
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input);
  auto nodeblockResult = nodeblockMachine->run();
  delete nodeblockMachine;

  const size_t EMPTY_REGEX_LENGTH = 2;
  if (nodeblockResult.regex.length() > EMPTY_REGEX_LENGTH)
    this->machine->setFreeOfContext(false);
  this->machine->incorporateFrom(nodeblockResult);

  char x;
  this->input >> x;
  
  if (this->input.eof())
  {
    // set to true because there is no middle and right contexts
    this->machine->setFreeOfContext(true);
    return new EndNodenameState(this->machine);
  }

  if (x == '[')
  {
    this->machine->setResultType(NodenameInfoType::NODE_PLACEHOLDER);
    this->machine->setPlaceholder(Placeholder::CUT);
    return new MiddleCutNodenameState(this->machine);
  }
  else if (x == '{')
  {
    this->machine->setResultType(NodenameInfoType::NODE_PLACEHOLDER);
    this->machine->setPlaceholder(Placeholder::COPY);
    return new MiddleCopyNodenameState(this->machine);
  }

  throw Exceptions::InvalidCharacterException(x);
}
