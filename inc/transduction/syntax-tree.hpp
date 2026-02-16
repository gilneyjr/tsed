#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <ostream>
#include <string>
#include <vector>

namespace Transduction
{
  class SyntaxTree
  {
  private:
    static std::string getNextTokenFromStream(std::istream&);
    static void putTokenBackToStream(std::string&, std::istream&);
    static std::vector<SyntaxTree*> parseTrees(std::istream&);
    static std::vector<SyntaxTree*> parseTreesOpt(std::istream&);
    static SyntaxTree* parseTree(std::istream&);
    static std::string parseWord(std::istream&);
  
  protected:
    std::string tag;
    SyntaxTree* parent;
    SyntaxTree* firstChild;
    SyntaxTree* lastChild;
    SyntaxTree* leftSibling;
    SyntaxTree* rightSibling;

  public:
    SyntaxTree(
      const std::string, SyntaxTree* = nullptr,
      SyntaxTree* = nullptr, SyntaxTree* = nullptr,
      SyntaxTree* = nullptr, SyntaxTree* = nullptr
    );
    ~SyntaxTree();
    
    const std::string& getTag() const;
    SyntaxTree* getParent() const;
    SyntaxTree* getFirstChild() const;
    SyntaxTree* getLastChild() const;
    SyntaxTree* getLeftSibling() const;
    SyntaxTree* getRightSibling() const;
    void addChild(SyntaxTree*);

    static SyntaxTree* createEndMarkerOnLeftOf(SyntaxTree*);
    static SyntaxTree* createEndMarkerOnRightOf(SyntaxTree*);
    static SyntaxTree* createEndMarkerAbove(SyntaxTree*);
    static SyntaxTree* createEndMarkerBellow(SyntaxTree*);

    static std::vector<SyntaxTree*> readFromFile(std::string&);
    friend std::ostream& operator<<(std::ostream&, const SyntaxTree&);
  };

  std::ostream& operator<<(std::ostream&, const SyntaxTree&);
}

#endif
