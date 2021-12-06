#include "ModelHierarchy.hpp"

#include <iostream>

MH::ModelHierachy::ModelHierachy()
    : world_(new Node("World", nullptr))
{
}

MH::ModelHierachy::~ModelHierachy()
{
    delete world_;
}

MH::Node *MH::ModelHierachy::addModel(std::shared_ptr<Model> model, std::string name, Node *parentNode)
{
    if ( parentNode == nullptr ) parentNode = world_;
    return new Node(name, model, parentNode);
}

void MH::ModelHierachy::printHierarchy(bool data) const
{
    world_->printHierarchy(data);
}

MH::Node *MH::ModelHierachy::findNodePath(std::string nodePath)
{
    return world_->findNodePath(nodePath);
}
