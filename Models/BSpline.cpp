#include "BSpline.hpp"

MH::BSpline::BSpline(size_t cPointNum, size_t subdiv)
{
    addCount_("subdiv", false, subdiv);
    addCount_("cpnum", false, cPointNum);
    addPointArray_("cp", false, cPointNum);
    addPointArray_("tangent", false, cPointNum);
    addPointArray_("vtx", true);
    createControlPoints_();
}

void MH::BSpline::changeParam_(std::string name)
{
    if ( name == "cpnum" && (pointArrays_["cp"].cols() != counts_["cpnum"])) createControlPoints_();
    if ( name == "cp" || name == "tangent" || name == "subdiv" )
        updateVtx();
}

void MH::BSpline::readParam_(std::string name)
{
}

void MH::BSpline::createControlPoints_()
{
    auto controlPointNum = counts_["cpnum"];

    if ( pointArrays_["cp"].cols() != controlPointNum)
        pointArrays_["cp"].resize(4, controlPointNum);
    pointArrays_["cp"].setZero();
    pointArrays_["cp"].row(3).setOnes();

    if ( pointArrays_["tangent"].cols() != controlPointNum)
        pointArrays_["tangent"].resize(4, controlPointNum);
    pointArrays_["tangent"].setZero();
    pointArrays_["tangent"].row(3).setOnes();
    auto subAngle = M_PI * 2 / (controlPointNum-1);
    for ( size_t index = 0; index < controlPointNum; index++ ) {
        auto angle = subAngle * index;
        auto cpX = cos(angle)*250;
        auto cpY = sin(angle)*250;
        auto tX = cos(angle+(M_PI/2))*100;
        auto tY = sin(angle+(M_PI/2))*100;
        pointArrays_["cp"](0, index) = cpX;
        pointArrays_["cp"](1, index) = cpY;
        pointArrays_["tangent"](0, index) = tX;
        pointArrays_["tangent"](1, index) = tY;
    }
    updateVtx();
}

void MH::BSpline::updateVtx()
{
    size_t cpNum = pointArrays_["cp"].cols();
    size_t vertexCount = ((cpNum-1)*3)+1;
    
    pointArrays_["vtx"].resize(4,vertexCount);
    size_t vIndex = 0;
    pointArrays_["vtx"].col(vIndex) = pointArrays_["cp"].col(0);
    for ( size_t index = 1; index < cpNum; index++ ) {
        vIndex++; pointArrays_["vtx"].col(vIndex) =
            pointArrays_["cp"].col(index-1) + pointArrays_["tangent"].col(index-1);
        pointArrays_["vtx"](3, vIndex) = 1;
        vIndex++; pointArrays_["vtx"].col(vIndex) =
            pointArrays_["cp"].col(index) - pointArrays_["tangent"].col(index);
        pointArrays_["vtx"](3, vIndex) = 1;
        vIndex++; pointArrays_["vtx"].col(vIndex) = pointArrays_["cp"].col(index);
    }

    size_t subdiv = getCount("subdiv");
    subdiv = pow(2,subdiv);
    size_t bPointsCount = subdiv*(cpNum-1)+1;
    Eigen::Array4Xd bPoints(4,bPointsCount);
    double t;
    size_t index = 0;
    size_t cpStart;
    for ( size_t cpIndex = 0; cpIndex < cpNum-1; cpIndex++) {
        cpStart = cpIndex*3;
        for ( size_t sub = 0; sub < subdiv; sub++) {
            t = (double) sub / subdiv;
            bPoints.col(index) = bezier_(t, cpStart, 3, 3);
            index++;
        }
    }
    bPoints.col(index) = pointArrays_["vtx"].col(vertexCount-1);
    pointArrays_["vtx"] = bPoints;
}

Eigen::Vector4d MH::BSpline::bezier_(double &t, size_t first, size_t i, size_t j)
{
    if ( j > 0 ) {
        return ((1.0-t)*bezier_(t, first,i-1,j-1) + t*bezier_(t, first,i,j-1));
    } else {
        return pointArrays_["vtx"].col(first+i);
    }
}
