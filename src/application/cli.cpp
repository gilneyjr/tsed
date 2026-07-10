#include "cli.hpp"

Application::CliOptions Application::Cli::parseArguments(int argc, char *argv[])
{
  CliOptions options;

  if (argc == 2)
  {
    std::string arg(argv[1]);

    if (arg == "-h" || arg == "--help")
    {
      options.action = CliAction::Help;
      return options;
    }

    if (arg == "-v" || arg == "--version")
    {
      options.action = CliAction::Version;
      return options;
    }
  }

  int i = 1;

  bool isTraversalOrderSetted = false;
  bool isTraversalBehaviorSetted = false;

  while (i < argc)
  {
    std::string arg(argv[i]);

    if (arg == "-h" || arg == "--help")
      throw std::invalid_argument("'" + arg + "' cannot be used with other arguments.");

    if (arg == "-v" || arg == "--version")
      throw std::invalid_argument("'" + arg + "' cannot be used with other arguments.");

    if (arg == "-o" || arg == "--output")
    {
      if (!options.outputDirectory.empty())
        throw std::invalid_argument("'" + arg + "' cannot be specified more than once.");

      options.outputDirectory = nextArgument(i, argc, argv, arg);
    }
    if (arg == "-t" || arg == "--traversal-order")
    {
      if (isTraversalOrderSetted)
        throw std::invalid_argument("'" + arg + "' cannot be specified more than once.");

      options.traversalOrder = parseTraversalOrder(nextArgument(i, argc, argv, arg));
      isTraversalOrderSetted = true;
    }
    if (arg == "-b" || arg == "--traversal-behavior")
    {
      if (isTraversalBehaviorSetted)
        throw std::invalid_argument("'" + arg + "' cannot be specified more than once.");

      options.traversalBehavior = parseTraversalBehavior(nextArgument(i, argc, argv, arg));
      isTraversalBehaviorSetted = true;
    }
    else if (!arg.empty() && arg.front() == '-')
      throw std::invalid_argument("unknown option '" + std::string(arg) + "'.");
    else
      break;

    ++i;
  }

  if (i >= argc)
    throw std::invalid_argument("missing TRANSDUCTION_RULE argument.");

  options.transductionRule = argv[i++];

  if (i >= argc)
    throw std::invalid_argument("missing input FILE argument.");

  while (i < argc)
    options.inputFiles.emplace_back(argv[i++]);
  
  return options;
}

void Application::Cli::printVersion(std::ostream& out)
{
  out << PROGRAM_NAME << ' ' << VERSION << '\n'
      << COPYRIGHT << '\n'
      << LICENSE << '\n';
}

void Application::Cli::printUsage(std::ostream& out)
{
  out << "Usage:\n"
      << "  " << PROGRAM_NAME << " [OPTIONS] TRANSDUCTION_RULE FILE...\n";
}

void Application::Cli::printHelp(std::ostream& out)
{
  printUsage(out);

  out << '\n'
      << "Apply a transduction rule defined by PATTERN to one or more syntax\n"
      << "trees read from FILEs.\n"
      << "The treebanks in each FILE must be written in the Penn Treebank format.\n"
      << '\n'
      << "Options:\n"
      << "  -o, --output DIRECTORY\n"
      << "      Write output files to DIRECTORY.\n"
      << '\n'
      << "  -h, --help\n"
      << "      Display this help and exit.\n"
      << '\n'
      << "  -v, --version\n"
      << "      Display version information and exit.\n"
      << '\n'
      << "Arguments:\n"
      << "  PATTERN\n"
      << "      File containing the transduction rules.\n"
      << '\n'
      << "  FILE...\n"
      << "      One or more input files containing syntax trees.\n"
      << '\n'
      << "Examples:\n"
      << "  tsed '[NP] ==> NNP' input.txt\n"
      << "  tsed '[NP] ==> NNP' input1.txt input2.txt\n"
      << "  tsed -o out '[NP] ==> NNP' input.txt\n"
      << "  tsed --output out '[NP] ==> NNP' input1.txt input2.txt\n"
      << '\n'
      << "Exit status 0 if any tree is modified, 1 if no tree is modified, and -1 in case of an error.\n";
}

void Application::Cli::printError(std::ostream& out, const std::string &message)
{
  out << PROGRAM_NAME << ": " << message << "\n\n";

  printUsage(out);

  out << "Try '" << PROGRAM_NAME << " --help' for more information.\n";
}

std::string Application::Cli::nextArgument(
  int& i,
  int argc,
  char* argv[],
  const std::string& option)
{
  ++i;
  if (i >= argc)
    throw std::invalid_argument("missing argument for '" + option + "'.");
  return argv[i];
}

Transduction::SyntaxTreeIteratorStrategyType Application::Cli::parseTraversalOrder(const std::string &order)
{
  using Transduction::SyntaxTreeIteratorStrategyType;

  if (order == "pre-order")
    return SyntaxTreeIteratorStrategyType::PRE_ORDER;

  if (order == "post-order")
    return SyntaxTreeIteratorStrategyType::POST_ORDER;

  throw std::invalid_argument(
      "unknown traversal order '" + order +
      "'. Expected one of: "
      "pre-order, "
      "post-order."
    );
}

Transduction::TraversalBehaviorType Application::Cli::parseTraversalBehavior(const std::string &behavior)
{
  using Transduction::TraversalBehaviorType;

  if (behavior == "follow-replacement")
    return TraversalBehaviorType::FOLLOW_REPLACEMENT;

  if (behavior == "skip-modified")
    return TraversalBehaviorType::SKIP_MODIFIED;

  if (behavior == "force-recursion")
    return TraversalBehaviorType::FORCE_RECURSION;

  if (behavior == "single-match")
    return TraversalBehaviorType::SINGLE_MATCH;

  if (behavior == "root-restart")
    return TraversalBehaviorType::ROOT_RESTART;

  throw std::invalid_argument(
    "unknown traversal behavior '" + behavior +
    "'. Expected one of: "
    "follow-replacement, "
    "skip-modified, "
    "force-recursion, "
    "single-match, "
    "root-restart."
  );
}