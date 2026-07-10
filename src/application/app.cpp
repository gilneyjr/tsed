#include "app.hpp"
#include "cli.hpp"
#include "parser.tab.h"
#include "transducer.hpp"
#include "transducer-builder.hpp"

#include <iostream>

int Application::App::run(int argc, char *argv[])
{
  try
  {
    CliOptions options = Cli::parseArguments(argc, argv);

    switch (options.action)
    {
    case CliAction::Help:
      Cli::printHelp(APP_OUTPUT);
      return 1; // TODO: create an enum for this
    case CliAction::Version:
      Cli::printVersion(APP_OUTPUT);
      return 1; // TODO: create an enum for this
    case CliAction::Run:
      return execute(options);
    }

    return 0;
  }
  catch (std::invalid_argument &e)
  {
    Cli::printError(APP_OUTPUT, e.what());
    return -1;
  }
}

int Application::App::execute(const CliOptions& options)
{
  std::cout << "OPTIONS\n";
  
  std::cout << "Action: ";
  switch (options.action)
  {
  case CliAction::Help:
    std::cout << "help\n";
    break;
  case CliAction::Run:
    std::cout << "run\n";
    break;
  case CliAction::Version:
    std::cout << "version\n";
    break;
  default:
    std::cout << "unknown\n";
    break;
  }

  std::cout << "Output Directory: " << (options.outputDirectory.empty() ? "not specified (using \"./\")" : options.outputDirectory) << "\n";

  std::cout << "Traversal Order: ";
  switch (options.traversalOrder)
  {
  case Transduction::SyntaxTreeIteratorStrategyType::PRE_ORDER:
    std::cout << "pre-order\n";
    break;
  case Transduction::SyntaxTreeIteratorStrategyType::POST_ORDER:
    std::cout << "post-order\n";
    break;
  default:
    std::cout << "unknown\n";
    break;
  }

  std::cout << "Traversal Behavior: ";
  switch (options.traversalBehavior)
  {
  case Transduction::TraversalBehaviorType::FOLLOW_REPLACEMENT:
    std::cout << "follow-replacement\n";
    break;
  case Transduction::TraversalBehaviorType::SKIP_MODIFIED:
    std::cout << "skip-modified\n";
    break;
  case Transduction::TraversalBehaviorType::FORCE_RECURSION:
    std::cout << "force-recursion\n";
    break;
  case Transduction::TraversalBehaviorType::SINGLE_MATCH:
    std::cout << "single-match\n";
    break;
  case Transduction::TraversalBehaviorType::ROOT_RESTART:
    std::cout << "root-restart\n";
    break;
  default:
    std::cout << "unknown\n";
    break;
  }

  std::cout << "Transduction Rule: " << options.transductionRule << "\n";
  std::cout << "Input Files:\n";
  for (auto &fileName : options.inputFiles)
    std::cout << "\t> " << fileName << "\n";

  std::cout << "\n";
  std::cout << "Running TSED...\n";


  auto rule = parseTransductionRule(options.transductionRule);

  Transduction::Transducer* transducer = Transduction::TransducerBuilder()
    .setIteratorStrategyType(options.traversalOrder)
    .setTraversalBehaviorType(options.traversalBehavior)
    .build();

  for (auto &filePath : options.inputFiles)
  {
    auto trees = Transduction::SyntaxTree::readFromFile(filePath);

    for (auto *tree : trees)
      transducer->transduce(rule, tree);
  }

  delete transducer;

  return 0;
}