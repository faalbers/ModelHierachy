#include "ChaikinCurve.hpp"

#include <iostream>

MH::ChaikinCurve::ChaikinCurve(size_t cPointNum, size_t recursions)
{
    addValue_("tx", 0); addValue_("ty", 0); addValue_("tz", 0);
    addValue_("rx", 0); addValue_("ry", 0); addValue_("rz", 0);
    addValue_("sx", 1); addValue_("sy", 1); addValue_("sz", 1);
    addCount_("recursions", recursions);
    addCount_("cpnum", cPointNum);
    addPointArray_("cp", cPointNum);
    updateControlPoints_();
    updateCurve_();
}

size_t MH::ChaikinCurve::vertexCount_(size_t cPointNum, size_t recursions) const
{
    if (recursions == 0) return cPointNum;
    return (2*(vertexCount_(cPointNum, recursions-1)-1));
}

void MH::ChaikinCurve::updateParams_()
{
    if ( pointArrays_["cp"].cols() != counts_["cpnum"] ) updateControlPoints_();
    updateCurve_();
}

void MH::ChaikinCurve::updateControlPoints_()
{
    double controlPointNum = counts_["cpnum"];
    pointArrays_["cp"].resize(4, controlPointNum);
    pointArrays_["cp"].row(3).setOnes();
    double subAngle = M_PI * 2 / (controlPointNum-1);
    for ( size_t index = 0; index < controlPointNum; index++ ) {
        double angle = subAngle * index;
        double x = -cos(angle)*250;
        double y = sin(angle)*250;
        pointArrays_["cp"](0, index) = x;
        pointArrays_["cp"](1, index) = y;
        pointArrays_["cp"](2, index) = 0;
    }
}

void MH::ChaikinCurve::updateCurve_()
{
    size_t controlPointNum = pointArrays_["cp"].cols();
    size_t recursions = counts_["recursions"];
    size_t vertexCount = vertexCount_(controlPointNum, recursions);
    vertices_.resize(4, vertexCount);
    vertices_.leftCols(controlPointNum) = pointArrays_["cp"];
    Eigen::Array4Xd tempVertices(vertexCount, 4);
    size_t tempCount = controlPointNum;
    for ( size_t recurs = 0; recurs < recursions; recurs++ )
        tempCount = chaikinAlgorthm_(tempVertices,tempCount);
}

size_t MH::ChaikinCurve::chaikinAlgorthm_(
    Eigen::Array4Xd &tempVertices,
    size_t tempCount)
{
    size_t newIndex = 0;
    for ( size_t pathIndex = 0; pathIndex < tempCount; pathIndex++ ) {
        if ( pathIndex == 0 ) continue;
        auto pathVector = vertices_.col(pathIndex) - vertices_.col(pathIndex-1);
        tempVertices.col(newIndex) = vertices_.col(pathIndex-1)+(pathVector * 0.25);
        newIndex++;
        tempVertices.col(newIndex) = vertices_.col(pathIndex-1)+(pathVector * 0.75);
        newIndex++;
    }
    vertices_.leftCols(newIndex) = tempVertices.leftCols(newIndex);
    return newIndex;
}