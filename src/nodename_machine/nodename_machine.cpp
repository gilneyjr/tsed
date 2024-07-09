#include "nodename_machine.hpp"
#include "begin_nodename_state.hpp"

Nodename::NodenameMachine::NodenameMachine(std::istream& input, std::ostream& output)
  : input(input), output(output)
{
  this->state = new Nodename::BeginNodenameState(this);
  this->finished = false;
}

Nodename::NodenameMachine::~NodenameMachine() 
{
  delete this->state;
}

void Nodename::NodenameMachine::finish()
{
  this->finished = true;
}

Nodename::NodenameResult::NodenameResult* Nodename::NodenameMachine::run() 
{
  this->resetResult();

  while (!this->finished && this->state != nullptr) 
  {
    NodenameState* nextState = this->state->run();
    if (this->state != nullptr && this->state != nextState) 
    {
      delete this->state;
      this->state = nextState;
    }
  }

  return this->result;
}

std::istream& Nodename::NodenameMachine::getInputStream() 
{
  return this->input;
}

std::ostream& Nodename::NodenameMachine::getOutputStream()
{
  return this->output;
}

void Nodename::NodenameMachine::setResultType(Nodename::NodenameResult::NodenameResultType type)
{
  this->result->type = type;
}

void Nodename::NodenameMachine::setPlaceholder(Nodename::NodenameResult::Placeholder placeholder)
{
  this->result->placeholder = placeholder;
}

void Nodename::NodenameMachine::setPlaceholderNumber(int number)
{
  this->result->placeholderNumber = number;
}

void Nodename::NodenameMachine::appendPlaceholderNumber(int number)
{
  int tmp = number;
  do {
    this->result->placeholderNumber *= 10;
    tmp /= 10;
  } while (tmp > 0);
  this->result->placeholderNumber += number;
}

void Nodename::NodenameMachine::setUndetermined(bool undetermined)
{
  this->result->undetermined = undetermined;
}

void Nodename::NodenameMachine::resetResult()
{
  if (this->result != nullptr)
    delete this->result;
  
  this->result = new Nodename::NodenameResult::NodenameResult(
    Nodename::NodenameResult::NodenameResultType::SIMPLE_NODE,
    Nodename::NodenameResult::Placeholder::NONE,
    -1,
    false,
    true,
    Nodename::NodenameResult::DefOrRef::NONE,
    true,
    true,
    nullptr
  );
}

void Nodename::NodenameMachine::setFreeOfContext(bool freeOfContext)
{
  this->result->freeOfContext = freeOfContext;
}

void Nodename::NodenameMachine::setDefOrRef(Nodename::NodenameResult::DefOrRef defOrRef)
{
  this->result->defOrRef = defOrRef;
}

void Nodename::NodenameMachine::setRegex(std::string input)
{
  this->result->regex += input;
}