#ifndef MH_NODE
#define MH_NODE

#include <string>
#include <set>

namespace MH
{

class Node
{
public:
    Node(std::string name, Node *parent = nullptr);
    ~Node();

    std::string         pathName() const;
    void                printHierarchy() const;

private:
    void                pathName_(std::string &pathName) const;

    std::string         name_;
    Node                *parent_;
    std::set<Node *>    children_;

};

}

#endif
