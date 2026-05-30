#ifndef REPLACEMENT_EXPRESSION_HPP
#define REPLACEMENT_EXPRESSION_HPP

#include "replacement-tree-sequence.hpp"
#include "replacement-validation-context.hpp"
#include "syntax-tree.hpp"
#include "symbol-table.hpp"

namespace Transduction::Replacement
{
  class ReplacementExpression
  {
  private:
    ReplacementTreeSequence *treeSequence;

    static std::map<unsigned int, NodenameMatch> cloneMatches(
      const std::map<unsigned int, NodenameMatch> &matches);

    static void deleteCutPlaceholdersFromTree(
      Transduction::SyntaxTree *tree,
      const std::map<unsigned int, NodenameMatch> &matches);

    std::vector<SyntaxTree*> generateTreesForReplacement(
      const std::map<unsigned int, NodenameMatch> &matches) const;

    static Transduction::SyntaxTree* markReplacementPoint(SymbolTable &symbolTable);

    static void injectGeneratedTrees(SyntaxTree *replacementPoint, std::vector<SyntaxTree*> &generatedTrees);
  public:
    ReplacementExpression(ReplacementTreeSequence *treeSequence);
    ~ReplacementExpression();
    std::vector<SyntaxTree*> replace(SyntaxTree *tree, SymbolTable &symbolTable);
    void validate(Contexts::ReplacementValidationContext &context) const;
  };    
}

#endif
