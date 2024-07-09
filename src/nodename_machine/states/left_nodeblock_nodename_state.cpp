#include "end_nodename_state.hpp"
#include "invalid_character_exception.hpp"
#include "left_nodeblock_nodename_state.hpp"
#include "middle_copy_nodename_state.hpp"
#include "middle_cut_nodename_state.hpp"
#include "nodeblock_machine.hpp"

Nodename::LeftNodeblockNodenameState::LeftNodeblockNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::LeftNodeblockNodenameState::~LeftNodeblockNodenameState() {}

Nodename::NodenameState* Nodename::LeftNodeblockNodenameState::run()
{
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input);
  nodeblockMachine->run();
  delete nodeblockMachine;

  if (this->output.tellp() > 0) // TODO: deixar isso mais claro
    this->machine->setFreeOfContext(false);

  char x;
  this->input >> x;
  
  if (this->input.eof())
    return new EndNodenameState(this->machine);

  if (x == '[')
  {
    this->machine->setResultType(Nodename::NodenameResult::NodenameResultType::NODE_PLACEHOLDER);
    this->machine->setPlaceholder(Nodename::NodenameResult::Placeholder::CUT);
    return new MiddleCutNodenameState(this->machine);
  }
  else if (x == '{')
  {
    this->machine->setResultType(Nodename::NodenameResult::NodenameResultType::NODE_PLACEHOLDER);
    this->machine->setPlaceholder(Nodename::NodenameResult::Placeholder::COPY);
    return new MiddleCopyNodenameState(this->machine);
  }

  throw Exceptions::InvalidCharacterException(x);
}
