#include "Model.hpp"

MH::Model::Model()
    : vertices_(0,4)
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
    values_[name] = value;
    update_();
}

const double &MH::Model::getValue(std::string name) const
{
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
    counts_[name] = value;
    update_();
}

const size_t &MH::Model::getCount(std::string name) const
{
    return counts_.at(name);
}

std::vector<std::string> MH::Model::getPointArrayNames() const
{
    std::vector<std::string> names;
    for ( auto &element : pointArrays_) names.push_back(element.first);
    return names;
}

size_t MH::Model::getPointArrayCount(std::string name) const
{
    return pointArrays_.at(name).rows();
}

Eigen::RowVector4d MH::Model::getPointFromArray(std::string name, size_t index) const
{
    return pointArrays_.at(name).row(index);
}

const Eigen::Matrix<double, Eigen::Dynamic, 4> &MH::Model::getPointArray(std::string name) const
{
    return pointArrays_.at(name);
}

void MH::Model::setPointInArray(std::string name, size_t index, double x, double y, double z)
{
    pointArrays_[name](index,0) = x;
    pointArrays_[name](index,1) = y;
    pointArrays_[name](index,2) = z;
    update_();
}

void MH::Model::addValue_(std::string name, double value) { values_[name] = value; }

void MH::Model::addCount_(std::string name, size_t value) { counts_[name] = value; }

void MH::Model::addPointArray_(std::string name, size_t size)
{
    Eigen::Matrix<double, Eigen::Dynamic, 4> pointArray(size,4);
    pointArray.setZero();
    pointArray.col(3).setOnes();
    pointArrays_[name] = pointArray;
}
