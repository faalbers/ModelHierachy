#include "Model.hpp"
#include <iostream>

MH::Model::Model()
{
}

std::vector<std::string> MH::Model::getValueNames() const
{
    std::vector<std::string> names;
    for ( auto &element : values_) names.push_back(element.first);
    return names;
}

void MH::Model::setValue(std::string name, double value)
{
    if ( values_.count(name) == 0 )
        error_("setValue: parameter with name '"+name+"' does not exist");
    values_[name] = value;
    updateParams_();
}

const double &MH::Model::getValue(std::string name) const
{
    if ( values_.count(name) == 0 )
        error_("getValue: parameter with name '"+name+"' does not exist");
    return values_.at(name);
}

std::vector<std::string> MH::Model::getCountNames() const
{
    std::vector<std::string> names;
    for ( auto &element : counts_) names.push_back(element.first);
    return names;
}

void MH::Model::setCount(std::string name, size_t value)
{
    if ( counts_.count(name) == 0 )
        error_("setCount: parameter with name '"+name+"' does not exist");
    counts_[name] = value;
    updateParams_();
}

const size_t &MH::Model::getCount(std::string name) const
{
    if ( counts_.count(name) == 0 )
        error_("getCount: parameter with name '"+name+"' does not exist");
    return counts_.at(name);
}

std::vector<std::string> MH::Model::getMatrixNames() const
{
    std::vector<std::string> names;
    for ( auto &element : matrices_) names.push_back(element.first);
    return names;
}

void MH::Model::setMatrix(std::string name, Eigen::Matrix4d matrix)
{
    if ( matrices_.count(name) == 0 )
        error_("setMatrix: parameter with name '"+name+"' does not exist");
    matrices_[name] = matrix;
    updateParams_();
}

const Eigen::Matrix4d &MH::Model::getMatrix(std::string name) const
{
    if ( matrices_.count(name) == 0 )
        error_("getMatrix: parameter with name '"+name+"' does not exist");
    return matrices_.at(name);
}

std::vector<std::string> MH::Model::getValueArrayNames() const
{
    std::vector<std::string> names;
    for ( auto &element : valueArrays_) names.push_back(element.first);
    return names;
}

size_t MH::Model::getValueArrayCount(std::string name) const
{
    if ( valueArrays_.count(name) == 0 )
        error_("getValueArrayCount: parameter with name '"+name+"' does not exist");
    return valueArrays_.at(name).size();
}

void MH::Model::setValueArray(std::string name, Eigen::ArrayXd &vArray)
{
    if ( valueArrays_.count(name) == 0 )
        error_("setValueArray: parameter with name '"+name+"' does not exist");
    valueArrays_[name] = vArray;
    updateParams_();
}

void MH::Model::setValueInArray(std::string name, size_t index, double value)
{
    if ( valueArrays_.count(name) == 0 )
        error_("setValueInArray: parameter with name '"+name+"' does not exist");
    valueArrays_[name](index) = value;
    updateParams_();
}

const Eigen::ArrayXd &MH::Model::getValueArray(std::string name) const
{
    if ( valueArrays_.count(name) == 0 )
        error_("getValueArray: parameter with name '"+name+"' does not exist");
    return valueArrays_.at(name);
}

double MH::Model::getValueFromArray(std::string name, size_t index) const
{
    if ( valueArrays_.count(name) == 0 )
        error_("getValueFromArray: parameter with name '"+name+"' does not exist");
    if ( index >= valueArrays_.at(name).size() )
        error_("getValueFromArray: parameter with name '"+name+"' out of bound index: "+std::to_string(index));
    return valueArrays_.at(name)(index);
}

std::vector<std::string> MH::Model::getPointArrayNames() const
{
    std::vector<std::string> names;
    for ( auto &element : pointArrays_) names.push_back(element.first);
    return names;
}

size_t MH::Model::getPointArrayCount(std::string name) const
{
    if ( pointArrays_.count(name) == 0 )
        error_("getPointArrayCount: parameter with name '"+name+"' does not exist");
    return pointArrays_.at(name).cols();
}

void MH::Model::setPointArray(std::string name, const Eigen::Array4Xd &pArray)
{
    if ( pointArrays_.count(name) == 0 )
        error_("setPointArray: parameter with name '"+name+"' does not exist");
    pointArrays_[name] = pArray;
    updateParams_();
}

void MH::Model::setPointInArray(std::string name, size_t index, double x, double y, double z)
{
    if ( pointArrays_.count(name) == 0 )
        error_("setPointInArray: parameter with name '"+name+"' does not exist");
    if ( index >= pointArrays_.at(name).cols() )
        error_("setPointInArray: parameter with name '"+name+"' out of bound index: "+std::to_string(index));
    pointArrays_[name](0, index) = x;
    pointArrays_[name](1, index) = y;
    pointArrays_[name](2, index) = z;
    updateParams_();
}

void MH::Model::setPointInArray(std::string name, size_t index, Eigen::Vector4d point)
{
    if ( pointArrays_.count(name) == 0 )
        error_("setPointInArray: parameter with name '"+name+"' does not exist");
    if ( index >= pointArrays_.at(name).cols() )
        error_("setPointInArray: parameter with name '"+name+"' out of bound index: "+std::to_string(index));
    pointArrays_[name](0, index) = point(0);
    pointArrays_[name](1, index) = point(1);
    pointArrays_[name](2, index) = point(2);

    updateParams_();
}

Eigen::Vector4d MH::Model::getPointFromArray(std::string name, size_t index) const
{
    if ( pointArrays_.count(name) == 0 )
        error_("getPointFromArray: parameter with name '"+name+"' does not exist");
    if ( index >= pointArrays_.at(name).rows() )
        error_("getPointFromArray: parameter with name '"+name+"' out of bound index: "+std::to_string(index));
    return pointArrays_.at(name).col(index);
}

const Eigen::Array4Xd &MH::Model::getPointArray(std::string name) const
{
    if ( pointArrays_.count(name) == 0 )
        error_("getPointArray: parameter with name '"+name+"' does not exist");
    return pointArrays_.at(name);
}

void MH::Model::addValue_(std::string name, double value) { values_[name] = value; }

void MH::Model::addValueArray_(std::string name, size_t size, double value)
{
    Eigen::ArrayXd valueArray(size);
    valueArray.setOnes();
    valueArray *= value;
    valueArrays_[name] = valueArray;
}

void MH::Model::addCount_(std::string name, size_t value) { counts_[name] = value; }

void MH::Model::addPointArray_(std::string name, size_t pointCount)
{
    Eigen::Array4Xd pointArray(4,pointCount);
    pointArray.setZero(); pointArray.row(3).setOnes();
    pointArrays_[name] = pointArray;
}

void MH::Model::error_(std::string message) const
{
    std::cout << "MH::Model:" << std::endl;
    std::cout << "-> " << message << std::endl;
    std::cout << "exit application ..." << std::endl;
    exit(1);
}
