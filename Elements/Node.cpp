#include "Node.hpp"
#include <iostream>

MH::Node::Node(std::string name, Node *parent)
    : name_(name)
    , model_(nullptr)
    , parent_(parent)
    , tx_(0), ty_(0), tz_(0), rx_(0), ry_(0), rz_(0), sx_(1), sy_(1), sz_(1)
{
    if ( parent != nullptr) parent_->children_.insert(this);
    frame_.setIdentity();
    transform_.setIdentity();
}

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

Eigen::Matrix4d MH::Node::getTransformInverse() const
{
    return getTransform().inverse();
}

Eigen::Array4Xd MH::Node::getTransformedVertices() const
{
    auto transformed = model_->getPointArray("vtx");
    //auto transformed = model_->getVertices();
    transformed = getTransform() * transformed.matrix();
    return transformed;
}

std::shared_ptr<MH::Model> MH::Node::getModel() const
{
    return model_;
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

void MH::Node::setFrameAxisX(double x, double y, double z)
{
    frame_(0,0) = x; frame_(1,0) = y; frame_(2,0) = z;
}

void MH::Node::setFrameAxisY(double x, double y, double z)
{
    frame_(0,1) = x; frame_(1,1) = y; frame_(2,1) = z;
}

void MH::Node::setFrameAxisZ(double x, double y, double z)
{
    frame_(0,2) = x; frame_(1,2) = y; frame_(2,2) = z;
}

void MH::Node::setFramePosition(double x, double y, double z)
{
    frame_(0,3) = x; frame_(1,3) = y; frame_(2,3) = z;
}

void MH::Node::pathName_(std::string &pathName) const
{
    if (parent_ != nullptr) parent_->pathName_(pathName);
    pathName += "/"+name_;
}

void MH::Node::setTransform_()
{
    // reset transform
    transform_.setIdentity();

    // set translate
    Eigen::Translation3d translate(tx_,ty_,tz_);

    // set rotation
    Eigen::AngleAxisd rotX(rx_, Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd rotY(ry_, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd rotZ(rz_, Eigen::Vector3d::UnitZ());

    // set scale
    Eigen::AlignedScaling3d scale(sx_,sy_,sz_);

    // creating affine transformation
    Eigen::Transform<double,3,Eigen::Affine> transform;
    transform = translate * rotX * rotY * rotZ * scale;

    // set transform
    transform_ = transform.matrix();
}

void MH::Node::getTransform_(Eigen::Matrix4d &transform) const
{
    if (parent_ != nullptr) {
        transform = transform_ * transform;
        parent_->getTransform_(transform);
    } else transform = frame_ * transform_ * transform;
}
