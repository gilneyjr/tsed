#include "copy_number_nodename_state.hpp"
#include "invalid_character_exception.hpp"
#include "middle_copy_nodename_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::MiddleCopyNodenameState::MiddleCopyNodenameState(
  Nodename::NodenameMachine* machine): 
  Nodename::NodenameState(machine) {}

Nodename::MiddleCopyNodenameState::~MiddleCopyNodenameState() {}

Nodename::NodenameState* Nodename::MiddleCopyNodenameState::run()
{
  char x;
  this->input >> x;

  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (std::isdigit(x))
  {
    this->machine->appendToPlaceholderNumber(x-'0');
    return new CopyNumberNodenameState(this->machine);
  }
  
  throw Exceptions::InvalidCharacterException(x);
}
