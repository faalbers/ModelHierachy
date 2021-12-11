#ifndef MH_BSPLINE
#define MH_BSPLINE

#include "Model.hpp"

namespace MH
{

class BSpline : public Model
{
public:
    BSpline(size_t cPointNum = 3);

private:
    void            updateParams_();
    void            updateControlPoints_();
    void            updateCurve_();
    Eigen::Vector4d bezier_(double &t, size_t first, size_t i, size_t j);
};

}

#endif
