#include "Node.hpp"

#include <iostream>

MH::Node::Node(std::string name, Node *parent)
    : name_(name)
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
    std::cout << pathName() << std::endl;
    for ( auto &child : children_ ) child->printHierarchy();
}

void MH::Node::pathName_(std::string &pathName) const
{
    if (parent_ != nullptr) parent_->pathName_(pathName);
    pathName += "/"+name_;
}
