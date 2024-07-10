#include "invalid_character_exception.hpp"
#include "middle_cut_nodeblock_nodename_state.hpp"
#include "nodeblock_machine.hpp"
#include "right_nodeblock_nodename_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::MiddleCutNodeblockNodenameState::MiddleCutNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::MiddleCutNodeblockNodenameState::~MiddleCutNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::MiddleCutNodeblockNodenameState::run()
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

  if (x == ']')
    return new RightNodeblockNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
