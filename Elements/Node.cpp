#include "Node.hpp"

#include <iostream>

MH::Node::Node(std::string name, std::shared_ptr<Model> model, Node *parent)
    : name_(name)
    , model_(model)
    , parent_(parent)
    , tx_(0), ty_(0), tz_(0), rx_(0), ry_(0), rz_(0), sx_(1), sy_(1), sz_(1)
{
    if ( parent != nullptr) parent_->children_.insert(this);
    frame_.setIdentity();
    transform_.setIdentity();
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

Eigen::Matrix4d MH::Node::getTransform() const
{
    Eigen::Matrix4d transform = frame_;
    getTransform_(transform);
    return transform;
}

void MH::Node::printHierarchy(bool data) const
{
    std::cout << pathName();
    if (model_ != nullptr ) std::cout << " (" << model_.use_count() << ")";
    std::cout << std::endl;
    if ( data ) {
        std::cout << "Frame:\n";
        std::cout << frame_ << std::endl;
        std::cout << "Transform:\n";
        std::cout << transform_ << std::endl;
    }
    for ( auto &child : children_ ) child->printHierarchy(data);
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

void MH::Node::setTx(double x) { tx_ = x; setTransform_(); }

void MH::Node::setTy(double y) { ty_ = y; setTransform_(); }

void MH::Node::setTz(double z) { tz_ = z; setTransform_(); }

void MH::Node::setRx(double x) { rx_ = x; setTransform_(); }

void MH::Node::setRy(double y) { ry_ = y; setTransform_(); }

void MH::Node::setRz(double z) { rz_ = z; setTransform_(); }

void MH::Node::setSx(double x) { sx_ = x; setTransform_(); }

void MH::Node::setSy(double y) { sy_ = y; setTransform_(); }

void MH::Node::setSz(double z) { sz_ = z; setTransform_(); }

void MH::Node::pathName_(std::string &pathName) const
{
    if (parent_ != nullptr) parent_->pathName_(pathName);
    pathName += "/"+name_;
}

void MH::Node::setTransform_()
{
    // reset transform
    transform_.setIdentity();

    // do scale
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> scaleMatrix(4,4);
    scaleMatrix.setIdentity();
    scaleMatrix(0,0) = sx_;
    scaleMatrix(1,1) = sy_;
    scaleMatrix(2,2) = sz_;
    transform_ *= scaleMatrix;

    // do rotate ZYX order
    Eigen::AngleAxisd rollAngle(rz_, Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd yawAngle(ry_, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd pitchAngle(rx_, Eigen::Vector3d::UnitX());
    Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> rotationMatrix(3,3);
    rotationMatrix = q.matrix();
    rotationMatrix.conservativeResize(4,4);
    rotationMatrix.row(3) << 0,0,0,1;
    rotationMatrix.col(3) << 0,0,0,1;
    transform_ *= rotationMatrix;

    // do translate
    transform_(3,0) = tx_;
    transform_(3,1) = ty_;
    transform_(3,2) = tz_;
}

void MH::Node::getTransform_(Eigen::Matrix4d &transform) const
{

    if (parent_ != nullptr) {
        transform *= transform_;
        parent_->getTransform_(transform);
    }
}
