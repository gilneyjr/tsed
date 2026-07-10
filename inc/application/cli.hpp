#ifndef CLI_HPP
#define CLI_HPP

#include "traversal-behavior-type.hpp"
#include "syntax-tree-iterator-strategy-type.hpp"

#include <ostream>
#include <string>
#include <vector>

namespace Application
{
  inline constexpr auto PROGRAM_NAME = "tsed";
  inline constexpr auto VERSION = "1.0.0";
  inline constexpr auto COPYRIGHT = "Copyright (C) 2026 Gilney Junior";
  inline constexpr auto LICENSE = "License MIT";

  enum class CliAction
  {
    Run,
    Help,
    Version
  };

  struct CliOptions
  {
    CliAction action = CliAction::Run;
    std::string outputDirectory;
    Transduction::SyntaxTreeIteratorStrategyType traversalOrder = Transduction::SyntaxTreeIteratorStrategyType::PRE_ORDER;
    Transduction::TraversalBehaviorType traversalBehavior = Transduction::TraversalBehaviorType::SKIP_MODIFIED;
    std::string transductionRule;
    std::vector<std::string> inputFiles;
  };

  class Cli
  {
  public:
    static CliOptions parseArguments(int argc, char* argv[]);
    static void printHelp(std::ostream &out);
    static void printVersion(std::ostream &out);
    static void printError(std::ostream &out, const std::string &message);

  private:
    static void printUsage(std::ostream &out);
    static std::string nextArgument(int& i, int argc, char* argv[], const std::string& option);
    static Transduction::SyntaxTreeIteratorStrategyType parseTraversalOrder(const std::string &order);
    static Transduction::TraversalBehaviorType parseTraversalBehavior(const std::string &behavior);
  };
}

#endif
