#include "double_quoted_escape_nodeblock_state.hpp"
#include "double_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::DoubleQuotedEscapeNodeblockState::DoubleQuotedEscapeNodeblockState(
    Nodename::Nodeblock::NodeblockMachine* machine):
    Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::DoubleQuotedEscapeNodeblockState::~DoubleQuotedEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::DoubleQuotedEscapeNodeblockState::run()
{
    std::istream& in = *(this->machine->getInputStream());
    std::ostream& out = *(this->machine->getOutputStream());

    if (in.eof())
        /* TODO: throw new Exception("fim de stream inválido.") */;
    
    char x;
    in >> x;

    if (true /* x in <special> */)
        out << "\\" << x;
    else
        out << x;
    return new DoubleQuotedNodeblockState(this->machine);
}