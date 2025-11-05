#include "unexpected-end-of-input-exception.hpp"

const char* Exceptions::UnexpectedEndOfInputException::what() const throw()
{
  return "Unexpected end of input.";
}
