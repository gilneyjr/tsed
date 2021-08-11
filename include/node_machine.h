#ifndef MACHINE_H
#define MACHINE_H

#include "structs.h"
#include <string>

class Machine {

public:
  Machine(std::string node_name);
  ~Machine();
  Nodespec execute();

private:
  int state, position, parenthesis,
      input_size, brackets_flag,
      sought_parenthesis, parsed_number,
      just_an_instance_flag, dots_count, dots_flag;

  char quote_type, delimiter_type;

  std::string input, output, errors, number;

  void parse_error();

  void normal_flow();
  void normal_flow_escape();
  void quoted_flow();
  void quoted_flow_escape();
  void regex_flow();
  void regex_flow_escape();
  void numbering();
  void consuming_dots();


};

#endif // MACHINE_H
