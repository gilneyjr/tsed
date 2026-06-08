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
    bool _isEndMarker = false;

    SyntaxTree() = default;
  public:
    class EndMarker;
    class ReplacementPoint;

    SyntaxTree(
      const std::string tag, SyntaxTree *parent = nullptr,
      SyntaxTree *firstChild = nullptr, SyntaxTree *lastChild = nullptr,
      SyntaxTree *leftSibling = nullptr, SyntaxTree *rightSibling = nullptr
    );
    virtual ~SyntaxTree();
    const std::string& getTag() const;
    void setTag(const std::string &tag);
    SyntaxTree* getParent() const;
    SyntaxTree* getFirstChild() const;
    SyntaxTree* getLastChild() const;
    SyntaxTree* getLeftSibling() const;
    SyntaxTree* getRightSibling() const;
    void addChild(SyntaxTree *child);
    void addLeftSibling(SyntaxTree *newLeftSibling);
    void addRightSibling(SyntaxTree *newRightSibling);
    bool isEndMarker();
    bool isInSubtree(SyntaxTree *subtree);
    SyntaxTree* clone() const;
    void detachSubtree();

    static SyntaxTree* createEndMarkerOnLeftOf(SyntaxTree *tree);
    static SyntaxTree* createEndMarkerOnRightOf(SyntaxTree *tree);
    static SyntaxTree* createEndMarkerAbove(SyntaxTree *tree);
    static SyntaxTree* createEndMarkerBellow(SyntaxTree *tree);
    static void destroyEndMarker(SyntaxTree *endMarker);
    static SyntaxTree* deleteSubtrees(std::vector<SyntaxTree*> &subtrees);

    static std::vector<SyntaxTree*> readFromFile(std::string &filename);
    friend std::ostream& operator<<(std::ostream &os, const SyntaxTree &tree);
  };

  std::ostream& operator<<(std::ostream &os, const SyntaxTree &tree);

  class SyntaxTree::EndMarker : public SyntaxTree
  {
  public:
    EndMarker();
  };

  class SyntaxTree::ReplacementPoint : public SyntaxTree
  {
  public:
    ReplacementPoint();
  };
}

#endif
