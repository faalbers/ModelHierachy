#include "BSpline.hpp"

#include <iostream>

MH::BSpline::BSpline(size_t cPointNum)
{
    addCount_("cpnum", cPointNum);
    addPointArray_("cp", cPointNum);
    addValueArray_("tangle", cPointNum);
    addValueArray_("tsize", cPointNum);
    updateControlPoints_();
    updateCurve_();
}

void MH::BSpline::updateParams_()
{
    if ( pointArrays_["cp"].cols() != counts_["cpnum"] ) updateControlPoints_();
    updateCurve_();
}

void MH::BSpline::updateControlPoints_()
{
    auto controlPointNum = counts_["cpnum"];
    pointArrays_["cp"].resize(4, controlPointNum);
    pointArrays_["cp"].setZero();
    pointArrays_["cp"].row(3).setOnes();
    valueArrays_["tangle"].resize(controlPointNum,1);
    valueArrays_["tsize"].resize(controlPointNum,1);
    valueArrays_["tsize"].setOnes();
    valueArrays_["tsize"] *= 100;
    auto subAngle = M_PI * 2 / (controlPointNum-1);
    for ( size_t index = 0; index < controlPointNum; index++ ) {
        auto angle = subAngle * index;
        auto x = cos(angle)*250;
        auto y = sin(angle)*250;
        pointArrays_["cp"](0, index) = x;
        pointArrays_["cp"](1, index) = y;
        pointArrays_["cp"](2, index) = 0;
        valueArrays_["tangle"](index) = angle + (M_PI/2);
    }
}

void MH::BSpline::updateCurve_()
{
    size_t cpCount = pointArrays_["cp"].cols();
    size_t vertexCount = ((cpCount-1)*3)+1;
    vertices_.resize(4,vertexCount);
    Eigen::Vector4d cpA = pointArrays_["cp"].col(0);
    size_t vIndex = 0;
    vertices_.col(vIndex) = pointArrays_["cp"].col(0);
    Eigen::Vector4d cpTemp;
    for ( size_t index = 1; index < cpCount; index++ ) {
        cpTemp(0) = cos(valueArrays_["tangle"](index-1));
        cpTemp(1) = sin(valueArrays_["tangle"](index-1));
        cpTemp *= valueArrays_["tsize"](index-1);
        cpTemp += cpA;
        cpTemp(2) = 0; cpTemp(3) = 1;

        vIndex++; vertices_.col(vIndex) = cpTemp;

        cpA = pointArrays_["cp"].col(index);

        cpTemp(0) = -cos(valueArrays_["tangle"](index));
        cpTemp(1) = -sin(valueArrays_["tangle"](index));
        cpTemp *= valueArrays_["tsize"](index-1);
        cpTemp += cpA;
        cpTemp(2) = 0; cpTemp(3) = 1;

        vIndex++; vertices_.col(vIndex) = cpTemp;
        vIndex++; vertices_.col(vIndex) = cpA;
    }

    size_t subdiff = 20;
    size_t bPointsCount = subdiff*(cpCount-1)+1;
    Eigen::Array4Xd bPoints(4,bPointsCount);
    double t;
    size_t index = 0;
    size_t cpStart;
    for ( size_t cpIndex = 0; cpIndex < cpCount-1; cpIndex++) {
        cpStart = cpIndex*3;
        for ( size_t sub = 0; sub < subdiff; sub++) {
            t = (double) sub / subdiff;
            bPoints.col(index) = bezier_(t, cpStart, 3, 3);
            index++;
        }
    }
    bPoints.col(index) = vertices_.col(vertexCount-1);
    vertices_ = bPoints;
}

Eigen::Vector4d MH::BSpline::bezier_(double &t, size_t first, size_t i, size_t j)
{
    if ( j > 0 ) {
        return ((1.0-t)*bezier_(t,first,i-1,j-1) + t*bezier_(t,first,i,j-1));
    } else {
        return vertices_.col(first+i);
    }
}
