#include "cut_number_nodename_state.hpp"
#include "middle_cut_nodeblock_nodename_state.hpp"
#include "middle_cut_nodename_state.hpp"
#include "unexpected_end_of_input_exception.hpp"
#include <cctype>

Nodename::MiddleCutNodenameState::MiddleCutNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::MiddleCutNodenameState::~MiddleCutNodenameState() {}

Nodename::NodenameState* Nodename::MiddleCutNodenameState::run()
{
  char x;
  this->input >> x;

  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (std::isdigit(x))
  {
    this->machine->appendToPlaceholderNumber(x-'0');
    return new CutNumberNodenameState(this->machine);
  }
  else
  {
    this->input.unget();
    return new MiddleCutNodeblockNodenameState(this->machine);
  }
}
