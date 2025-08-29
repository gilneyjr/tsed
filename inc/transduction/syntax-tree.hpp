#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <string>
#include <vector>

namespace Transduction
{
  class SyntaxTree
  {
  public:
    // TODO: turn some attributes to protected
    std::string tag;
    SyntaxTree* parent;
    SyntaxTree* firstChild;
    SyntaxTree* lastChild;
    SyntaxTree* leftSibling;
    SyntaxTree* rightSibling;

    SyntaxTree(const std::string, SyntaxTree* = nullptr);
    ~SyntaxTree();
    void addChild(SyntaxTree*);
    static std::vector<SyntaxTree*> readFromFile(std::string&);
  
  static void printTree(SyntaxTree*, int = 0);
  private:
    static std::string getNextTokenFromStream(std::istream&);
    static void putTokenBackToStream(std::string&, std::istream&);
    static std::vector<SyntaxTree*> parseTrees(std::istream&);
    static std::vector<SyntaxTree*> parseTreesOpt(std::istream&);
    static SyntaxTree* parseTree(std::istream&);
    static std::string parseWord(std::istream&);
  };
}

#endif