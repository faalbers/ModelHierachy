#ifndef MH_NODE
#define MH_NODE

#include <string>
#include <set>
#include <memory>
#include "../Models/Model.hpp"

namespace MH
{

class Node
{
public:
    Node(std::string name, std::shared_ptr<Model> model, Node *parent = nullptr);
    ~Node();

    std::string pathName() const;
    void        printHierarchy() const;
    Node        *findNodePath(std::string nodePath);

private:
    void        pathName_(std::string &pathName) const;

    std::string             name_;
    Node                    *parent_;
    std::set<Node *>        children_;
    std::shared_ptr<Model>  model_;
};

}

#endif
