#include "normal_escape_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"

Nodename::Nodeblock::NormalEscapeNodeblockState::NormalEscapeNodeblockState(
    Nodename::Nodeblock::NodeblockMachine* machine):
    Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::NormalEscapeNodeblockState::~NormalEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::NormalEscapeNodeblockState::run()
{
    std::istream& in = *(this->machine->getInputStream());
    std::ostream& out = *(this->machine->getOutputStream());

    if (in.eof())
        /* TODO: throw new Exception("fim de stream inesperado."); */;

    char x;
    in >> x;

    if (x != '\\')
    {
        out << x;
        return new NormalNodeblockState(this->machine);
    }
    // TODO: ver o que acontece nos casos em que x == '\\'

    return this;
}