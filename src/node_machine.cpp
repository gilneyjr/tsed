#include "node_machine.h"
#include <string>
#include <ctype.h>
#include <sstream>

#define NORMAL_STATE          0
#define NORMAL_ESCAPE_STATE   1
#define QUOTED_STATE          2
#define QUOTED_ESCAPE_STATE   3
#define REGEX_STATE           4
#define REGEX_ESCAPE_STATE    5
#define NUMBERING_STATE       6
#define CONSUMING_DOTS        7

using namespace std;

Machine::Machine(string node_name)
{
  state = NORMAL_STATE;
  position = 0;
  parenthesis = 1;
  input_size = 0;
  brackets_flag = 0;
  just_an_instance_flag = 0;
  sought_parenthesis = 0;
  parsed_number = -1;
  quote_type = 0;
  delimiter_type = 0;
  dots_count = 0;
  dots_flag = 0;

  input = node_name;
}

Machine::~Machine()
{

}

Nodespec Machine::execute()
{
  input_size = input.length();

  output = string("^(");
  errors = string();

  while(position < input_size)
  {
    switch(state)
    {
      case NORMAL_STATE: normal_flow();
      break;
      case NORMAL_ESCAPE_STATE: normal_flow_escape();
      break;
      case QUOTED_STATE: quoted_flow();
      break;
      case QUOTED_ESCAPE_STATE: quoted_flow_escape();
      break;
      case REGEX_STATE: regex_flow();
      break;
      case REGEX_ESCAPE_STATE: regex_flow_escape();
      break;
      case NUMBERING_STATE: numbering();
      break;
      case CONSUMING_DOTS: consuming_dots();
      break;
    }

    if(!errors.empty())
    {
      break;
    }
  }

  output.push_back(')');
  output.push_back('$');

  Nodespec node_spec;

  if(errors.empty())
  {
    node_spec.type_of_nodespec = dots_flag ? RANGE_PLACEHOLDER : SIMPLE_NODE;
    node_spec.regex = output;

    if(delimiter_type == '[')
    {
      node_spec.type = just_an_instance_flag ? CUT_PLACEHOLDER_REF : CUT_PLACEHOLDER_FULL;
      node_spec.holder_number = parsed_number;
    }
    else if(delimiter_type == '{')
    {
      node_spec.type = just_an_instance_flag ? COPY_PLACEHOLDER_REF : CUT_PLACEHOLDER_FULL;
      node_spec.holder_number = parsed_number;
    }
    else
    {
      node_spec.type = NONE;
    }
  }
  else
  {
    node_spec.type_of_nodespec = NODE_EXCEPTION;
    node_spec.errors = errors;
  }

  node_spec.parenthesis = parenthesis;
  node_spec.holder_start = sought_parenthesis;

  return node_spec;

}

void Machine::parse_error()
{
  stringstream error;
  error << "<program> does not know how interpret " << input << " at column "<< position << ".";
  errors = error.str();
}

void Machine::normal_flow()
{
  char current = input[position];

  if( brackets_flag == 1 && current != ']' && current != '}' ) just_an_instance_flag = 0;

  if( isalnum(current) || current == '-' || current == '_' )
  {
    output.push_back(current);
  }
  else if( ( current == '[' || current == '{' ) && brackets_flag == 0 )
  {
    output.push_back(')');
    output.push_back('(');
    parenthesis++;
    sought_parenthesis = parenthesis;
    delimiter_type = current;
    brackets_flag++;

    state = NUMBERING_STATE;
    number = string();
  }
  else if( ( current == ']' || current == '}' ) && brackets_flag == 1 )
  {
    if( delimiter_type == '{' && current == ']' )
      errors = "Unmatched '{'.";
    if( delimiter_type == '[' && current == '}' )
      errors = "Unmatched '['.";
    output.push_back(')');
    output.push_back('(');
    parenthesis++;
    brackets_flag++;
  }
  else if( current == '[' || current == '{' )
  {
    errors = "You may open brackets just once.";
  }
  else if( ( current == ']' || current == '}' ) && brackets_flag == 0 )
  {
    errors = "You should open a bracket first.";
  }
  else if( ( current == ']' || current == '}' ) && brackets_flag == 2 )
  {
    errors = "You should close a bracket just once.";
  }
  else if( current == '*' )
  {
    output.push_back('.');
    output.push_back('*');
  }
  else if( current == '?' )
  {
    output.push_back(current);
  }
  else if( current == '.' )
  {
    dots_count++;
    dots_flag = 1;
    state = CONSUMING_DOTS;
  }
  else if( current == '(' )
  {
    output.push_back(current);
    parenthesis++;
  }
  else if( current == '"' || current == '\'' )
  {
     quote_type = current;
     state = QUOTED_STATE;
  }
  else if( current == ')' )
  {
    output.push_back(current);
  }
  else if( current == '\\' )
  {
    state = NORMAL_ESCAPE_STATE;
  }
  else if( current == '/' )
  {
    state = REGEX_STATE;
  }
  else
  {
     parse_error();
  }

  if( errors.empty() ) position++;
}

void Machine::normal_flow_escape()
{
  char current = input[position];

  if( current == '(' ||  current == ')' ||  current == '^' ||
      current == '$' ||  current == '[' ||  current == ']' ||
      current == '?' ||  current == '*' )
  {
    output.push_back('\\');
    output.push_back(current);
    state = NORMAL_STATE;
  }
  else if( current != ' ')
  {
    output.push_back(current);
    state = NORMAL_STATE;
  }
  else
  {
    parse_error();
  }

  if( errors.empty() ) position++;
}

void Machine::quoted_flow()
{
  char current = input[position];

  if( current == '\\' )
  {
    state = QUOTED_ESCAPE_STATE;
  }
  else if( current == quote_type)
  {
    state = NORMAL_STATE;
  }
  else
  {
    output.push_back(current);
  }

  if( errors.empty() ) position++;
}

void Machine::quoted_flow_escape()
{
  char current = input[position];

  output.push_back(current);
  state = QUOTED_STATE;

  if( errors.empty() ) position++;
}

void Machine::regex_flow()
{
  char current = input[position];

  if( current == '/' )
  {
    state = NORMAL_STATE;
  }
  else if( current == '\\' )
  {
    state = REGEX_ESCAPE_STATE;
  }
  else if( current == '(' )
  {
    parenthesis++;
    output.push_back(current);
  }
  else
  {
    output.push_back(current);
  }

  if( errors.empty() ) position++;
}

void Machine::regex_flow_escape()
{
  char current = input[position];

  output.push_back(current);
  state = REGEX_STATE;

  if( errors.empty() ) position++;
}

void Machine::numbering()
{
  char current = input[position];

  if( isdigit(current) )
  {
    number.push_back(current);
  }
  else if( current == ':' )
  {
    just_an_instance_flag = 1;
    parsed_number = stoi(number);
    state = NORMAL_STATE;
  }
  else if( current == ']' || current == '}' || number.empty() )
  {
    // special case to permit [] and {}
    parsed_number = 0;
    position--;
    state = NORMAL_STATE;
  }
  else
  {
    errors = "You should separate the identifier and by a colon.";
  }

  if( errors.empty() ) position++;
}

void Machine::consuming_dots()
{
  char current = input[position];

  if( ( dots_count == 0 || dots_count == 1 ) && current == '.' )
  {
    dots_count++;
  }
  else if( dots_count == 2 && current == '.')
  {
    state = NORMAL_STATE;
  }
  else
  {
    errors = "You should write three dots in case you need a range filler.";
  }

  if( errors.empty() ) position++;
}
