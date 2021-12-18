#include "TestBox.hpp"

MH::TestBox::TestBox()
{
    addPointArray_("vtx", true, 9);
    pointArrays_["vtx"].col(0) << -300,  300, -250, 1;
    pointArrays_["vtx"].col(1) << -250,  250, -250, 1;
    pointArrays_["vtx"].col(2) <<  250,  250, -250, 1;
    pointArrays_["vtx"].col(3) <<  250, -250, -250, 1;
    pointArrays_["vtx"].col(4) << -250, -250, -250, 1;
    pointArrays_["vtx"].col(5) << -250,  250,  250, 1;
    pointArrays_["vtx"].col(6) <<  250,  250,  250, 1;
    pointArrays_["vtx"].col(7) <<  250, -250,  250, 1;
    pointArrays_["vtx"].col(8) << -250, -250,  250, 1;
}

void MH::TestBox::changeParam_(std::string name)
{
}

void MH::TestBox::readParam_(std::string name)
{
}

