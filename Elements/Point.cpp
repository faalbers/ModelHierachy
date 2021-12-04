#include "Point.hpp"

#include <iostream>

MH::Point::Point(double x, double y)
    : point_(3)
{
    point_.setUnit(2);
    point_[0] = x;
    point_[1] = y;
}

MH::Point::Point(double x, double y, double z)
    : point_(4)
{
    point_.setUnit(3);
    point_[0] = x;
    point_[1] = y;
    point_[2] = z;
}

size_t MH::Point::axes() const
{
    return point_.size()-1;
}

double& MH::Point::operator()(int index)
{
    if (index >= point_.size()) error_("index out of bound: " + std::to_string(index));
    return point_(0,index);
}

const double& MH::Point::operator()(int index) const
{
    if (index >= point_.size()) error_("index out of bound: " + std::to_string(index));
    return point_(0,index);
}

void MH::Point::error_(std::string message) const
{
    std::cout << "MH::Point:" << std::endl;
    std::cout << "-> " << message << std::endl;
    std::cout << "exit application ..." << std::endl;
    exit(1);
}

std::ostream & MH::operator<< (std::ostream &os, MH::Point const &rhs)
{
    auto elements = rhs.axes()+1;
    for ( int index= 0; index < elements; index++) {
        if ( index > 0 ) os << " ";
        os << rhs(index);
    }
    return os;
}