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
  auto nodeblockMachine = new Nodename::Nodeblock::NodeblockMachine(this->input, this->output);
  nodeblockMachine->run();
  delete nodeblockMachine;

  char x;
  this->input >> x;
  
  if (this->input.eof())
    return new EndNodenameState(this->machine);

  if (x == '[')
  {
    // TODO: colocar placeholder para CUT
    return new MiddleCutNodenameState(this->machine);
  }
  else if (x == '{')
  {
    // TODO: colocar placeholder para COPY
    return new MiddleCopyNodenameState(this->machine);
  }

  throw Exceptions::InvalidCharacterException(x);
}
