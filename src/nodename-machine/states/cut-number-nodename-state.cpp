#include "cut-number-nodename-state.hpp"
#include "invalid-character-exception.hpp"
#include "middle-cut-nodeblock-nodename-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

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
