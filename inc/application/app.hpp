#ifndef APP_HPP
#define APP_HPP

#include "cli.hpp"

namespace Application
{
  #define APP_OUTPUT std::cout

  class App
  {    
  public:
    static int run(int argc, char* argv[]);
  private:
    static int execute(const CliOptions &options);
  };
}

#endif
