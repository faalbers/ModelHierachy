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
    changeParam_(name);
}

const double &MH::Model::getValue(std::string name)
{
    if ( values_.count(name) == 0 )
        error_("getValue: parameter with name '"+name+"' does not exist");
    readParam_(name);
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
    changeParam_(name);
}

const size_t &MH::Model::getCount(std::string name)
{
    if ( counts_.count(name) == 0 )
        error_("getCount: parameter with name '"+name+"' does not exist");
    readParam_(name);
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
    changeParam_(name);
}

const Eigen::Matrix4d &MH::Model::getMatrix(std::string name)
{
    if ( matrices_.count(name) == 0 )
        error_("getMatrix: parameter with name '"+name+"' does not exist");
    readParam_(name);
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
    changeParam_(name);
}

void MH::Model::setValueInArray(std::string name, size_t index, double value)
{
    if ( valueArrays_.count(name) == 0 )
        error_("setValueInArray: parameter with name '"+name+"' does not exist");
    valueArrays_[name](index) = value;
    changeParam_(name);
}

const Eigen::ArrayXd &MH::Model::getValueArray(std::string name)
{
    if ( valueArrays_.count(name) == 0 )
        error_("getValueArray: parameter with name '"+name+"' does not exist");
    readParam_(name);
    return valueArrays_.at(name);
}

double MH::Model::getValueFromArray(std::string name, size_t index)
{
    if ( valueArrays_.count(name) == 0 )
        error_("getValueFromArray: parameter with name '"+name+"' does not exist");
    if ( index >= valueArrays_.at(name).size() )
        error_("getValueFromArray: parameter with name '"+name+"' out of bound index: "+std::to_string(index));
    readParam_(name);
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
    changeParam_(name);
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
    changeParam_(name);
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
    changeParam_(name);
}

Eigen::Vector4d MH::Model::getPointFromArray(std::string name, size_t index)
{
    if ( pointArrays_.count(name) == 0 )
        error_("getPointFromArray: parameter with name '"+name+"' does not exist");
    if ( index >= pointArrays_.at(name).rows() )
        error_("getPointFromArray: parameter with name '"+name+"' out of bound index: "+std::to_string(index));
    readParam_(name);
    return pointArrays_.at(name).col(index);
}

const Eigen::Array4Xd &MH::Model::getPointArray(std::string name)
{
    if ( pointArrays_.count(name) == 0 )
        error_("getPointArray: parameter with name '"+name+"' does not exist");
    readParam_(name);
    return pointArrays_.at(name);
}

void MH::Model::addParam_(std::string name, bool readOnly)
{
    if (
        valueArrays_.count(name) > 0 ||
        values_.count(name) > 0 ||
        valueArrays_.count(name) > 0 ||
        counts_.count(name) > 0 ||
        pointArrays_.count(name) > 0 ||
        matrices_.count(name) > 0 )
            error_("addParam: name already exists: "+name);
    params_[name] = readOnly;
}

void MH::Model::addValue_(std::string name, bool readOnly, double value)
{
    addParam_(name, readOnly);
    values_[name] = value;
}

void MH::Model::addMatrix_(std::string name, bool readOnly, Eigen::Matrix4d &matrix)
{
    addParam_(name, readOnly);
    matrices_[name] = matrix;
}

void MH::Model::addMatrix_(std::string name, bool readOnly)
{
    addParam_(name, readOnly);
    Eigen::Matrix4d matrix;
    matrix.setIdentity();
    matrices_[name] = matrix;
}

void MH::Model::addValueArray_(std::string name, bool readOnly, size_t size, double value)
{
    addParam_(name, readOnly);
    Eigen::ArrayXd valueArray(size);
    valueArray.setOnes();
    valueArray *= value;
    valueArrays_[name] = valueArray;
}

void MH::Model::addCount_(std::string name, bool readOnly, size_t value)
{
    addParam_(name, readOnly);
    counts_[name] = value;
}

void MH::Model::addPointArray_(std::string name, bool readOnly, size_t pointCount)
{
    addParam_(name, readOnly);
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
