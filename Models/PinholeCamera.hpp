#ifndef MH_PINHOLECAMERA
#define MH_PINHOLECAMERA

#include "Model.hpp"

namespace MH
{

class PinholeCamera : public Model
{
public:
    PinholeCamera(double near = 1.0, double = -1.0, double viewAngle = M_PI/3);

private:
    void    changeParam_(std::string name) override;
    void    readParam_(std::string name) override;
    void    updateMatrix();

    bool    doMatrixUpdate_; // status of matrix recalculation
};

}

#endif
