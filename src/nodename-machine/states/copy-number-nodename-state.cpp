#include "copy-number-nodename-state.hpp"
#include "invalid-character-exception.hpp"
#include "middle-copy-nodeblock-nodename-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

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
