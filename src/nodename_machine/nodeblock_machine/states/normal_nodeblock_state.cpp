#include <cctype>
#include "end_nodeblock_state.hpp"
#include "double_quoted_nodeblock_state.hpp"
#include "normal_escape_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"
#include "regex_nodeblock_state.hpp"
#include "single_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::NormalNodeblockState::NormalNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::NormalNodeblockState::~NormalNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::NormalNodeblockState::run() {
  char x;
  this->input >> x;
  
  if (this->input.eof()) 
  {
    this->output << ')';
    return new EndNodeblockState(this->machine);
  }

  if (x == '*')
    this->output << ".*";
  else if (x == '?')
    this-> output << ".";
  else if (std::isalnum(x) || x == '-' || x == '_')
    this->output << x;
  else if (x == '\'')
  {
    this->output << '(';
    return new SingleQuotedNodeblockState(this->machine);
  }
  else if (x == '"')
  {
    this->output << '(';
    return new DoubleQuotedNodeblockState(this->machine);
  }
  else if (x == '\\')
    return new NormalEscapeNodeblockState(this->machine);
  else if (x == '/')
  {
    this->output << '(';
    return new RegexNodeblockState(this->machine);
  } else; // TODO: implementar exceção informando caractere inválido

  return this;
}