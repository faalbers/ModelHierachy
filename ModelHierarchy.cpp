#include "ModelHierarchy.hpp"

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

void MH::ModelHierachy::setFrameAxisX(double x, double y, double z)
{
    world_->setFrameAxisX(x,y,z);
}

void MH::ModelHierachy::setFrameAxisY(double x, double y, double z)
{
    world_->setFrameAxisY(x,y,z);
}

void MH::ModelHierachy::setFrameAxisZ(double x, double y, double z)
{
    world_->setFrameAxisZ(x,y,z);
}

void MH::ModelHierachy::setFramePosition(double x, double y, double z)
{
    world_->setFramePosition(x,y,z);
}
