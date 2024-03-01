#include <sstream>
#include "nodeblock_machine.hpp"

using namespace Nodename::Nodeblock;

int main(int argc, char const *argv[])
{
  std::istream* input = new std::stringstream("NP-*");
  
  NodeblockMachine* machine = new NodeblockMachine(*input, std::cout);
  machine->run();

  delete machine;
  delete input;

  return 0;
}
