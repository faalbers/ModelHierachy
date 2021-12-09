#include "BSpline.hpp"

#include <iostream>

MH::BSpline::BSpline(size_t cPointNum)
{
    addCount_("cpnum", cPointNum);
    addPointArray_("cp", cPointNum);
    addValueArray_("tangle", cPointNum);
    addValueArray_("tsize", cPointNum);
    setupControlPoints_();
    updateCurve_();
}

void MH::BSpline::updateParams_()
{
    if ( pointArrays_["cp"].cols() != counts_["cpnum"] ) setupControlPoints_();
    updateCurve_();
}

void MH::BSpline::setupControlPoints_()
{
    auto controlPointNum = counts_["cpnum"];
    pointArrays_["cp"].resize(4, controlPointNum);
    pointArrays_["cp"].col(3).setOnes();
    valueArrays_["tangle"].resize(controlPointNum,1);
    valueArrays_["tsize"].resize(controlPointNum,1);
    valueArrays_["tsize"].setOnes();
    valueArrays_["tsize"] *= 20;
    auto subAngle = M_PI * 2 / (controlPointNum-1);
    for ( size_t index = 0; index < controlPointNum; index++ ) {
        auto angle = subAngle * index;
        auto x = -cos(angle)*250;
        auto y = sin(angle)*250;
        pointArrays_["cp"](0, index) = x;
        pointArrays_["cp"](1, index) = y;
        pointArrays_["cp"](2, index) = 0;
        auto tangentAngle = -angle - (M_PI/2);
        valueArrays_["tangle"](index) = tangentAngle;
    }
}

void MH::BSpline::updateCurve_()
{
    Eigen::Vector4d cpA = pointArrays_["cp"].col(0);
    Eigen::Vector4d cpTemp;
    std::cout << cpA << std::endl;
    for ( size_t index = 1; index < pointArrays_["cp"].cols(); index++ ) {
        cpTemp(0) = cos(valueArrays_["tangle"](index-1));
        cpTemp(1) = sin(valueArrays_["tangle"](index-1));
        cpTemp *= valueArrays_["tsize"](index-1);
        cpTemp += cpA;
        cpTemp(2) = 0; cpTemp(3) = 1;
        std::cout << cpTemp << std::endl;

        cpA = pointArrays_["cp"].col(index);

        cpTemp(0) = -cos(valueArrays_["tangle"](index));
        cpTemp(1) = -sin(valueArrays_["tangle"](index));
        cpTemp *= valueArrays_["tsize"](index-1);
        cpTemp += cpA;
        cpTemp(2) = 0; cpTemp(3) = 1;
        std::cout << cpTemp << std::endl;

        std::cout << cpA << std::endl;
    }
    /*
    double t;
    for ( int sub = 0; sub <= 10; sub++) {
        t = (double) sub / 50;
        //pathPoints.append(bezier_(t,controlPointNum-1,controlPointNum-1));
    }
    */
}
