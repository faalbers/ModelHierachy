#include "PinholeCamera.hpp"

MH::PinholeCamera::PinholeCamera(double near, double far, double fov,
    double screenWidth, double screenHeight)
    : doProjectUpdate_(true)
    , doScreenUpdate_(true)
{
    addValue_("near", false, near);
    addValue_("far", false, far);
    addValue_("fov", false, fov);
    addValue_("width", false, screenWidth);
    addValue_("height", false, screenHeight);
    addMatrix_("project", true);
    addMatrix_("screen", true);
}

void MH::PinholeCamera::changeParam_(std::string name)
{
    if ( name == "near" ) doProjectUpdate_ = true;
    else if ( name == "far" ) doProjectUpdate_ = true;
    else if ( name == "fov" ) doProjectUpdate_ = true;
    else if ( name == "width" ) doScreenUpdate_ = true;
    else if ( name == "height" ) doScreenUpdate_ = true;
}

void MH::PinholeCamera::readParam_(std::string name)
{
    if ( name == "project" ) updateProject_();
    if ( name == "screen" ) updateScreen_();
}

void MH::PinholeCamera::updateProject_()
{
    if ( !doProjectUpdate_ ) return;

    auto denum = values_["far"] - values_["near"];
    auto temp = 1.0/tan(values_["fov"]/2.0);
    matrices_["project"].setZero();
    matrices_["project"](0,0) = temp;
    matrices_["project"](1,1) = temp;
    matrices_["project"](2,2) = (values_["far"]+values_["near"])/denum;
    matrices_["project"](2,3) = -((values_["far"]*values_["near"]*2.0)/denum);
    matrices_["project"](3,2) = -1;
    
    doProjectUpdate_ = false;
}

void MH::PinholeCamera::updateScreen_()
{
    if ( !doScreenUpdate_ ) return;

    if ( values_["width"] == 0 || values_["height"] == 0 )
        error_("updateScreen_: width or height can not be zero");

    double widthDir = values_["width"]/abs(values_["width"]);
    double heightDir = values_["height"]/abs(values_["height"]);

    matrices_["screen"].setIdentity();
    matrices_["screen"](0,0) = values_["width"] / 2.0;
    matrices_["screen"](1,1) = values_["height"] / 2.0;
    matrices_["screen"](2,2) = 1.0;
    matrices_["screen"](0,3) = widthDir * values_["width"] / 2.0;
    matrices_["screen"](1,3) = heightDir * values_["height"] / 2.0;

    doScreenUpdate_ = false;
}