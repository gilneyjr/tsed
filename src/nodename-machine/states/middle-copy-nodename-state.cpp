#include "copy-number-nodename-state.hpp"
#include "invalid-character-exception.hpp"
#include "middle-copy-nodename-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

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
