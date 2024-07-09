#include <iostream>
#include <sstream>
#include "nodename_machine.hpp"
#include "nodeblock_machine.hpp"

using namespace Nodename;
using namespace Nodename::Nodeblock;

void testNodeblock()
{
  std::istream* input = new std::stringstream("NP-*");
  
  NodeblockMachine* machine = new NodeblockMachine(*input);
  machine->run();

  delete machine;
  delete input;
}

#include <regex>

void testRegex() 
{
  std::string nodeblockPattern;
  while (true)
  {
    std::cout << "Enter the Nodeblock Pattern: ";
    if (!(std::cin >> nodeblockPattern))
      break;

    std::istringstream* input = new std::istringstream(nodeblockPattern);
    std::ostringstream* output = new std::ostringstream();

    NodeblockMachine* machine = new NodeblockMachine(*input);
    machine->run();

    delete machine;
    delete input;

    std::cout << "Nodeblock Generated Pattern: " << output->str() << std::endl;
    std::regex pattern("^" + output->str() + "$");
    while (true)
    {
      std::cout << "Enter the Nodeblock to be recognized: ";
      std::string nodeblockStr;
      if (!(std::cin >> nodeblockStr))
        break;
      
      std::smatch matches;
      if (std::regex_match(nodeblockStr, matches, pattern))
        for (size_t i = 0; i < matches.size(); i++)
          std::cout << "Match [" << i << "]: " << matches[i] << std::endl;
    }
  }
}

void testRegex2() 
{
  std::regex pattern("^\\/$");

  std::string str;
  std::cin >> str;

  std::smatch matches;
  if (std::regex_match(str, matches, pattern))
    for (size_t i = 0; i < matches.size(); i++)
      std::cout << "Match [" << i << "]: " << matches[i] << std::endl;
}

void testNodename()
{
  std::string nodenamePattern;
  while (true)
  {
    std::cout << "Enter the Nodename Pattern: ";
    if (!(std::cin >> nodenamePattern))
      break;

    std::istringstream* input = new std::istringstream(nodenamePattern);
    std::ostringstream* output = new std::ostringstream();

    auto machine = new NodenameMachine(*input, *output);
    try 
    {
      machine->run();
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
    catch (const char* error)
    {
      std::cout << error << std::endl;
      return;
    }

    delete machine;
    delete input;

    std::cout << "Nodename Generated Pattern: " << output->str() << std::endl;
    std::regex pattern("^" + output->str() + "$");
    while (true)
    {
      std::cout << "Enter the Nodename to be recognized: ";
      std::string nodenameStr;
      if (!(std::cin >> nodenameStr))
        break;
      
      std::smatch matches;
      if (std::regex_match(nodenameStr, matches, pattern))
        for (size_t i = 0; i < matches.size(); i++)
          std::cout << "Match [" << matches.position(i) << "," << matches.position(i)+matches.length(i) << "]: " << matches[i] << std::endl;
    }
  }
}

int main(int argc, char const *argv[])
{
  testNodename();
  return 0;
}
