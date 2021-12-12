#include "ChaikinCurve.hpp"

MH::ChaikinCurve::ChaikinCurve(size_t cPointNum, size_t subdiv)
{
    addCount_("subdiv", subdiv);
    addCount_("cpnum", cPointNum);
    addPointArray_("cp", cPointNum);
    createControlPoints_();
}

Eigen::Array4Xd MH::ChaikinCurve::getVertices()
{
    size_t subdiv = counts_["subdiv"];
    size_t cpNum = pointArrays_["cp"].cols();
    size_t vertexCount = vertexCount_(cpNum, subdiv);

    Eigen::Array4Xd vertices(4,vertexCount);
    vertices.leftCols(cpNum) = pointArrays_["cp"];
    size_t tempCount = cpNum;
    for ( size_t recurs = 0; recurs < subdiv; recurs++ )
        tempCount = chaikinAlgorithm_(vertices,tempCount);

    return vertices;
}

void MH::ChaikinCurve::updateParams_()
{
    if ( pointArrays_["cp"].cols() != counts_["cpnum"] ) createControlPoints_();
}

void MH::ChaikinCurve::createControlPoints_()
{
    double controlPointNum = counts_["cpnum"];
    pointArrays_["cp"].resize(4, controlPointNum);
    pointArrays_["cp"].row(3).setOnes();
    double subAngle = M_PI * 2 / (controlPointNum-1);
    for ( size_t index = 0; index < controlPointNum; index++ ) {
        double angle = subAngle * index;
        double x = cos(angle)*250;
        double y = sin(angle)*250;
        pointArrays_["cp"](0, index) = x;
        pointArrays_["cp"](1, index) = y;
        pointArrays_["cp"](2, index) = 0;
    }
}

size_t MH::ChaikinCurve::vertexCount_(size_t cPointNum, size_t subdiv) const
{
    if (subdiv == 0) return cPointNum;
    return (2*(vertexCount_(cPointNum, subdiv-1)-1));
}

size_t MH::ChaikinCurve::chaikinAlgorithm_(
    Eigen::Array4Xd &vertices,
    size_t tempCount)
{
    Eigen::Array4Xd tempVertices = vertices;
    size_t newIndex = 0;
    for ( size_t pathIndex = 0; pathIndex < tempCount; pathIndex++ ) {
        if ( pathIndex == 0 ) continue;
        auto pathVector = tempVertices.col(pathIndex) - tempVertices.col(pathIndex-1);
        vertices.col(newIndex) = tempVertices.col(pathIndex-1)+(pathVector * 0.25);
        newIndex++;
        vertices.col(newIndex) = tempVertices.col(pathIndex-1)+(pathVector * 0.75);
        newIndex++;
    }
    return newIndex;
}
