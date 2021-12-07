#include "ChaikinCurve.hpp"

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
    if ( pointArrays_["cp"].rows() != counts_["cpnum"] ) updateControlPoints_();
    updateCurve_();
}

void MH::ChaikinCurve::updateControlPoints_()
{
    auto controlPointNum = counts_["cpnum"];
    pointArrays_["cp"].resize(controlPointNum,4);
    pointArrays_["cp"].col(3).setOnes();
    auto subAngle = M_PI * 2 / (controlPointNum-1);
    for ( size_t index = 0; index < controlPointNum; index++ ) {
        auto angle = subAngle * index;
        auto x = -cos(angle)*250;
        auto y = sin(angle)*250;
        pointArrays_["cp"](index,0) = x;
        pointArrays_["cp"](index,1) = y;
        pointArrays_["cp"](index,2) = 0;
    }
}

void MH::ChaikinCurve::updateCurve_()
{
    auto controlPointNum = pointArrays_["cp"].rows();
    auto recursions = counts_["recursions"];
    size_t vertexCount = vertexCount_(controlPointNum, recursions);
    vertices_.resize(vertexCount, 4);
    vertices_.topRows(controlPointNum) = pointArrays_["cp"];
    Eigen::Matrix<double, Eigen::Dynamic, 4> tempVertices(vertexCount,4);
    size_t tempCount = controlPointNum;
    for ( size_t recurs = 0; recurs < recursions; recurs++ )
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