#ifndef REPLACEMENT_NODE_HPP
#define REPLACEMENT_NODE_HPP

#include <vector>
#include "nodename_info.hpp"

namespace Ast
{
  // TODO: Verify if the struct need to be improved
  struct ReplacementNode
  {
    Nodename::NodenameInfo* nodenameInfo;
    std::vector<ReplacementNode*>* children;

    ReplacementNode(Nodename::NodenameInfo* nodenameInfo) : nodenameInfo(nodenameInfo) {}
    ReplacementNode(
      Nodename::NodenameInfo* nodenameInfo, 
      std::vector<ReplacementNode*>* children
    ) : nodenameInfo(nodenameInfo), children(children) {}

    ~ReplacementNode()
    {
      if (nodenameInfo != nullptr)
        delete nodenameInfo;
      
      if (children != nullptr)
      {
        for (ReplacementNode *child : *children)
          delete child;
        delete children;
      }
    }
  };
}

#endif
