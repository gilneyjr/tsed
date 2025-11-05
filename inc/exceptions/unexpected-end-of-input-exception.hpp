#ifndef UNEXPECTED_END_OF_INPUT_EXCEPTION_HPP
#define UNEXPECTED_END_OF_INPUT_EXCEPTION_HPP

#include <exception>

namespace Exceptions
{
  class UnexpectedEndOfInputException: public std::exception
  {
  public:
    virtual const char* what() const throw();
  };
}

#endif
