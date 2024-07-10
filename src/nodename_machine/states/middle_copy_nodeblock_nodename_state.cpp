#include "invalid_character_exception.hpp"
#include "middle_copy_nodeblock_nodename_state.hpp"
#include "nodeblock_machine.hpp"
#include "right_nodeblock_nodename_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::MiddleCopyNodeblockNodenameState::MiddleCopyNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::MiddleCopyNodeblockNodenameState::~MiddleCopyNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::MiddleCopyNodeblockNodenameState::run()
{
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input);
  auto nodeblockResult = nodeblockMachine->run();
  delete nodeblockMachine;

  if (nodeblockResult.regex.length() > 0)
    this->machine->setDefOrRef(NodenameResult::DefOrRef::DEFINITION);
  else
    this->machine->setDefOrRef(NodenameResult::DefOrRef::REFERENCE);
  this->machine->incorporateFrom(nodeblockResult);

  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == '}')
    return new RightNodeblockNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
