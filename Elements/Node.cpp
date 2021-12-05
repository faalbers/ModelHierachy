#include "Node.hpp"

#include <iostream>

MH::Node::Node(std::string name, std::shared_ptr<Model> model, Node *parent)
    : name_(name)
    , model_(model)
    , parent_(parent)
{
    if ( parent != nullptr) parent_->children_.insert(this);
}

MH::Node::~Node()
{
    if ( parent_ != nullptr) parent_->children_.erase(this);
    for ( auto &child : children_ ) {
        child->parent_ = nullptr;
        delete child;
    }
}

std::string MH::Node::pathName() const
{
    std::string pathName = "";
    pathName_(pathName);
    return pathName;
}

void MH::Node::printHierarchy() const
{
    std::cout << pathName();
    if (model_ != nullptr ) std::cout << " (" << model_.use_count() << ")";
    std::cout << std::endl;
    for ( auto &child : children_ ) child->printHierarchy();
}

MH::Node *MH::Node::findNodePath(std::string nodePath)
{
    if ( pathName() == nodePath ) return this;
    Node *foundNode = nullptr;
    for ( auto &child : children_ ) {
        foundNode = child->findNodePath(nodePath);
        if ( foundNode != nullptr ) break;
    }
    return foundNode;
}

void MH::Node::pathName_(std::string &pathName) const
{
    if (parent_ != nullptr) parent_->pathName_(pathName);
    pathName += "/"+name_;
}
