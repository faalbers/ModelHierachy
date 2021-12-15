#include "TestBox.hpp"

MH::TestBox::TestBox()
{
    addPointArray_("vtx", true, 8);
    pointArrays_["vtx"].col(0) << -200,  200, -200, 1;
    pointArrays_["vtx"].col(1) <<  200,  200, -200, 1;
    pointArrays_["vtx"].col(2) <<  200, -200, -200, 1;
    pointArrays_["vtx"].col(3) << -200, -200, -200, 1;
    pointArrays_["vtx"].col(4) << -200,  200,  200, 1;
    pointArrays_["vtx"].col(5) <<  200,  200,  200, 1;
    pointArrays_["vtx"].col(6) <<  200, -200,  200, 1;
    pointArrays_["vtx"].col(7) << -200, -200,  200, 1;
}

void MH::TestBox::changeParam_(std::string name)
{
}

void MH::TestBox::readParam_(std::string name)
{
}

