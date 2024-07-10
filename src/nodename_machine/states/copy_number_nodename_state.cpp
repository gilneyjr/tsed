#include "copy_number_nodename_state.hpp"
#include "invalid_character_exception.hpp"
#include "middle_copy_nodeblock_nodename_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::CopyNumberNodenameState::CopyNumberNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::CopyNumberNodenameState::~CopyNumberNodenameState() {}

Nodename::NodenameState* Nodename::CopyNumberNodenameState::run()
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
    return new MiddleCopyNodeblockNodenameState(this->machine);

  throw Exceptions::InvalidCharacterException(x);
}
