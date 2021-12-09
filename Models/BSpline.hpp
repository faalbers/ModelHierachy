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
    void    updateParams_();
    void    updateControlPoints_();
    void    updateCurve_();
};

}

#endif
