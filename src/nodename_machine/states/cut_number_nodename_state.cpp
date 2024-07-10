#include "cut_number_nodename_state.hpp"
#include "invalid_character_exception.hpp"
#include "middle_cut_nodeblock_nodename_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::CutNumberNodenameState::CutNumberNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::CutNumberNodenameState::~CutNumberNodenameState() {}

Nodename::NodenameState* Nodename::CutNumberNodenameState::run()
{
  char x;
  this->input >> x;

  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (std::isdigit(x))
  {
    this->machine->appendToPlaceholderNumber(x-'0');
    return this;
  }
  else if (x == ':')
    return new MiddleCutNodeblockNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
