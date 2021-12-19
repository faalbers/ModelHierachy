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

MH::Node *MH::ModelHierachy::addParent(std::string name, Node *parentNode)
{
    if ( parentNode == nullptr ) parentNode = world_;
    return new Node(name, parentNode);
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

Eigen::Matrix4d MH::ModelHierachy::screenTransform(int width, int height)
{
    if ( width == 0 || height == 0 )
        error_("screenTransform: width or height can not be zero");
    Eigen::Matrix4d screenM;
    double widthDir = (double) (width/abs(width));
    double heightDir = (double) (height/abs(height));

    screenM.setIdentity();
    screenM(0,0) = (double) width / 2.0;
    screenM(1,1) = (double) height / 2.0;
    screenM(2,2) = 1.0;
    screenM(0,3) = widthDir * width / 2.0;
    screenM(1,3) = heightDir * height / 2.0;
    return screenM;
}

void MH::ModelHierachy::pointsToScreen(Node *modelNode, Node *cameraNode, Eigen::Array4Xd &points)
{
    points =
        cameraNode->getModel()->getMatrix("project") *
        modelNode->getTransformTo(cameraNode) *
        points.matrix();
    for ( auto point : points.colwise() ) point /= point(3);
    points = cameraNode->getModel()->getMatrix("screen") * points.matrix();
}

void MH::ModelHierachy::screenToPoints(Node *modelNode, Node *cameraNode, Eigen::Array4Xd &points)
{
    Eigen::Matrix4d transform =
        cameraNode->getModel()->getMatrix("project") *
        modelNode->getTransformTo(cameraNode);
    points = cameraNode->getModel()->getMatrix("screen").inverse() * points.matrix();
    points = transform.inverse() * points.matrix();
    for ( auto point : points.colwise() ) point /= point(3);
    points.row(3).setOnes();
}

void MH::ModelHierachy::error_(std::string message)
{
    std::cout << "MH::ModelHierachy:" << std::endl;
    std::cout << "-> " << message << std::endl;
    std::cout << "exit application ..." << std::endl;
    exit(1);
}
