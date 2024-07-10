#include "nodename_machine.hpp"
#include "begin_nodename_state.hpp"

Nodename::NodenameMachine::NodenameMachine(std::istream& input)
  : input(input)
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

Nodename::NodenameResult::NodenameResult Nodename::NodenameMachine::run() 
{
  this->result = NodenameResult::NodenameResult();

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

std::istream& Nodename::NodenameMachine::getInputStream() // Trocar isso para simplesmente char nextInputChar();
{
  return this->input;
}

void Nodename::NodenameMachine::setResultType(Nodename::NodenameResult::NodenameResultType type)
{
  this->result.type = type;
}

void Nodename::NodenameMachine::setPlaceholder(Nodename::NodenameResult::Placeholder placeholder)
{
  this->result.placeholder = placeholder;
}

void Nodename::NodenameMachine::appendToPlaceholderNumber(int number) // TODO: fazer um teste unitário para esta função
{
  int tmp = number;
  do {
    this->result.placeholderNumber *= 10;
    tmp /= 10;
  } while (tmp > 0);
  this->result.placeholderNumber += number;
}

void Nodename::NodenameMachine::setFreeOfContext(bool freeOfContext)
{
  this->result.freeOfContext = freeOfContext;
}

void Nodename::NodenameMachine::setDefOrRef(Nodename::NodenameResult::DefOrRef defOrRef)
{
  this->result.defOrRef = defOrRef;
}

void Nodename::NodenameMachine::appendToRegex(std::string input)
{
  this->result.regex += input;
}

void Nodename::NodenameMachine::incorporateFrom(Nodename::Nodeblock::NodeblockResult result)
{
  this->result.undetermined = this->result.undetermined || result.undetermined;
  this->result.regex += result.regex;
}