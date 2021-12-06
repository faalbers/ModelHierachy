#include "ChaikinCurve.hpp"

#include <iostream>

MH::ChaikinCurve::ChaikinCurve(size_t cPointNum, size_t recursions)
    : controlPointNum_(cPointNum)
    , recursions_(recursions)
    , controlPoints_(controlPointNum_,4)
{
    updateControlPoints_();
}

void MH::ChaikinCurve::setControlPointNum(size_t controlPointNum)
{
    controlPointNum_ = controlPointNum;
    updateControlPoints_();
}

void MH::ChaikinCurve::setControlPoint(size_t index, double x, double y, double z)
{
    controlPoints_(index,0) = x;
    controlPoints_(index,1) = y;
    controlPoints_(index,2) = z;
    updateCurve_();
}

void MH::ChaikinCurve::setControlPointX(size_t index, double val)
{
    controlPoints_(index,0) = val;
    updateCurve_();
}

void MH::ChaikinCurve::setControlPointY(size_t index, double val)
{
    controlPoints_(index,1) = val;
    updateCurve_();
}

void MH::ChaikinCurve::setControlPointZ(size_t index, double val)
{
    controlPoints_(index,2) = val;
    updateCurve_();
}

Eigen::Matrix<double, Eigen::Dynamic, 4> MH::ChaikinCurve::getControlPoints() const
{
    Eigen::Matrix<double, Eigen::Dynamic, 4> cpCopy(controlPoints_.rows(),4);
    cpCopy = controlPoints_;
    return cpCopy;
}

size_t MH::ChaikinCurve::vertexCount_(size_t cPointNum, size_t recursions) const
{
    if (recursions == 0) return cPointNum;
    return (2*(vertexCount_(cPointNum, recursions-1)-1));
}

void MH::ChaikinCurve::updateControlPoints_()
{
    controlPoints_.resize(controlPointNum_,4);
    auto subAngle = M_PI / (controlPointNum_-1);
    for ( size_t index = 0; index < controlPointNum_; index++ ) {
        auto angle = subAngle * index;
        auto x = -cos(angle)*100;
        auto y = sin(angle)*100;
        controlPoints_.row(index) << x, y, 0, 1;
    }
    updateCurve_();
}

void MH::ChaikinCurve::updateCurve_()
{
    size_t vertexCount = vertexCount_(controlPointNum_, recursions_);
    vertices_.resize(vertexCount, 4);
    vertices_.topRows(controlPointNum_) = controlPoints_;
    Eigen::Matrix<double, Eigen::Dynamic, 4> tempVertices(vertexCount,4);
    size_t tempCount = controlPointNum_;
    for ( size_t recurs = 0; recurs < recursions_; recurs++ )
        tempCount = chaikinAlgorthm_(tempVertices,tempCount);
}

size_t MH::ChaikinCurve::chaikinAlgorthm_(
    Eigen::Matrix<double, Eigen::Dynamic, 4> &tempVertices,
    size_t tempCount)
{
    size_t newIndex = 0;
    for ( size_t pathIndex = 0; pathIndex < tempCount; pathIndex++ ) {
        if ( pathIndex == 0 ) continue;
        auto pathVector = vertices_.row(pathIndex) - vertices_.row(pathIndex-1);
        tempVertices.row(newIndex) = vertices_.row(pathIndex-1)+(pathVector * 0.25);
        newIndex++;
        tempVertices.row(newIndex) = vertices_.row(pathIndex-1)+(pathVector * 0.75);
        newIndex++;
    }
    vertices_.topRows(newIndex) = tempVertices.topRows(newIndex);
    return newIndex;
}