#include "Frame.hpp"

#include <iostream>

MH::Frame::Frame(double xAxis, double yAxis)
    : frame_(3,3)
{
    frame_.setIdentity();
    frame_(0,0) = xAxis;
    frame_(1,1) = yAxis;
}

MH::Frame::Frame(double xAxis, double yAxis, double zAxis)
    : frame_(4,4)
{
    frame_.setIdentity();
    frame_(0,0) = xAxis;
    frame_(1,1) = yAxis;
    frame_(2,2) = zAxis;
}

size_t MH::Frame::axes() const
{
    return frame_.rows()-1;
}

double& MH::Frame::operator()(int row, int column)
{
    if (row >= frame_.rows()) error_("row out of bound: " + std::to_string(row));
    if (column >= frame_.cols()) error_("column out of bound: " + std::to_string(column));
    return frame_(row,column);
}

const double& MH::Frame::operator()(int row, int column) const
{
    if (row >= frame_.rows()) error_("row out of bound: " + std::to_string(row));
    if (column >= frame_.cols()) error_("column out of bound: " + std::to_string(column));
    return frame_(row,column);
}

void MH::Frame::error_(std::string message) const
{
    std::cout << "MH::Frame:" << std::endl;
    std::cout << "-> " << message << std::endl;
    std::cout << "exit application ..." << std::endl;
    exit(1);
}

std::ostream & MH::operator<< (std::ostream &os, MH::Frame const &rhs)
{
    auto elements = rhs.axes()+1;
    for ( int row = 0; row < elements; row++) {
        for ( int column = 0; column < elements; column++) {
            if ( column > 0 ) os << " ";
            os << rhs(row,column);
        }
        os << std::endl;
    }
    return os;
}
