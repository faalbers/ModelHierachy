#include "PointArray.hpp"

#include <iostream>

MH::PointArray::PointArray(size_t pointsNum)
    : points_(pointsNum,4)
{
    points_.setOnes();
}