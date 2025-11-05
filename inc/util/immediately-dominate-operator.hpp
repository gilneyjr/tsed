#ifndef IMMEDIATELY_DOMINATE_OPERATOR_HPP
#define IMMEDIATELY_DOMINATE_OPERATOR_HPP

#include <string>
#include <list>
#include <regex>

#include "nodename-info.hpp"

// TODO: make a tree after
struct Tree
{
  std::string tag;
  std::list<Tree> children;
};

bool isImmediatelyDominatedBy(Nodename::NodenameInfo nodenameInfo, Tree treeToSearch)
{
  std::regex pattern("^" + nodenameInfo.regex + "$");
  for (Tree &child : treeToSearch.children)
    if (std::regex_match(child.tag, pattern))
      return true;
  return false;
}

#endif