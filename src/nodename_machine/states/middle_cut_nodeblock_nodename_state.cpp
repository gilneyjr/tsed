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
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input, this->output);
  nodeblockMachine->run();
  delete nodeblockMachine;

  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == ']')
    return new RightNodeblockNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
