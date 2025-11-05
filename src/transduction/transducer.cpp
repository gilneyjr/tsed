#include <climits>
#include <iostream> // TODO: Remove it later
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "transducer.hpp"

Transduction::Transducer::Transducer(TransversalStrategy* transversalStrategy)
  : transversalStrategy(transversalStrategy) {}

Transduction::Transducer::~Transducer()
{
  if (this->transversalStrategy)
    delete this->transversalStrategy;
}

void Transduction::Transducer::apply(TransductionRule *rule, SyntaxTree* tree)
{
  if (rule == nullptr || tree == nullptr)
    return;

  transversalStrategy->start(tree);
  while (transversalStrategy->hasNext())
  {
    SyntaxTree* current = transversalStrategy->next();
    SymbolTable symbolTable;
    if (rule->search->match(current, symbolTable))
    {
      std::cout << *current << std::endl;
      this->transversalStrategy->notifyTransduction();
      // TODO: apply replacement expression here
    }
  }
}

// TODO: remove these comments later
// NP >> [0:PP]
// NP < [0:PP] // Poderia entrar embaixo do NP, mas não no PP
// NP $, [0:PP] // Poderia entrar nos filhos de NP sem problema
// NP $. [0:PP] // Não poderia entrar no PP
// 3 possíveis comportamentos:
// 1. Continua a partir do placeholder como se ele estivesse 
//    já sido processado, se ele estiver adiante do tree na preorder.
// 2. Armazena em um conjunto as árvores já alteradas e não permite 
//    entrar nos filhos delas.
// 3. Permitir recursividade
