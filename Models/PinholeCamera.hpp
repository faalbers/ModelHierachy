#ifndef MH_PINHOLECAMERA
#define MH_PINHOLECAMERA

#include "Model.hpp"

namespace MH
{

class PinholeCamera : public Model
{
public:
    PinholeCamera(
        double near, double far,
        double fov,
        double screenWidth, double screenHeight);

private:
    void    changeParam_(std::string name) override;
    void    readParam_(std::string name) override;
    void    updateProject_();
    void    updateScreen_();
};

}

#endif
