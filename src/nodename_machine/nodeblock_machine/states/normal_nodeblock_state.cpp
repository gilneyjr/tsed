#include "end_nodeblock_state.hpp"
#include "normal_escape_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"

Nodename::Nodeblock::NormalNodeblockState::NormalNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::NormalNodeblockState::~NormalNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::NormalNodeblockState::run() {
  std::istream& in = *(this->machine->getInputStream());
  std::ostream& out = *(this->machine->getOutputStream());

  if (in.eof()) 
  {
    out << ")";
    return new EndNodeblockState(this->machine);
  }

  char x;
  in >> x;

  if (true /*TODO: x in <alnum> U {-}*/)
    out << x;
  else if (x == '*')
    out << ".*";
  else if (x == '?')
    out << ".";
  else if (x == '"') 
  {
    out << "(";
    return new DoubleQuotedNodeblockState(this->machine);
  }
  else if (x == '\'') 
  {
    out << "(";
    return new SingleQuotedNodeblockState(this->machine);
  }
  else if (x == '/')
  {
    out << "(";
    return new RegexNodeblockState(this->machine);
  }
  else if (x == '\\')
    return new NormalEscapeNodeblockState(this->machine); 
  else
    /* TODO: throw new Exception("Entrada inválida");*/;

  return this;
}