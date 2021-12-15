#include "PinholeCamera.hpp"

MH::PinholeCamera::PinholeCamera(double near, double far, double viewAngle)
    : doMatrixUpdate_(true)
{
    addValue_("near", false, near);
    addValue_("far", false, far);
    addValue_("vangle", false, viewAngle);
    addMatrix_("matrix", true);
}

void MH::PinholeCamera::changeParam_(std::string name)
{
    if ( name == "near" ) doMatrixUpdate_ = true;
    else if ( name == "far" ) doMatrixUpdate_ = true;
    else if ( name == "vangle" ) doMatrixUpdate_ = true;
}

void MH::PinholeCamera::readParam_(std::string name)
{
    if ( name == "matrix" ) updateMatrix();
}

void MH::PinholeCamera::updateMatrix()
{
    if ( !doMatrixUpdate_ ) return;

    auto denum = values_["far"] - values_["near"];
    matrices_["matrix"].setZero();
    matrices_["matrix"](0,0) = cos(values_["vangle"]/2.0);
    matrices_["matrix"](1,1) = cos(values_["vangle"]/2.0);
    matrices_["matrix"](2,2) = (values_["far"]+values_["near"])/denum;
    matrices_["matrix"](2,3) = (values_["far"]*values_["near"]*2.0)/denum;
    matrices_["matrix"](3,2) = -1;
    
    doMatrixUpdate_ = false;
}