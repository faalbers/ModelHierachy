#ifndef MH_BSPLINE
#define MH_BSPLINE

#include "Model.hpp"

namespace MH
{

class BSpline : public Model
{
public:
    BSpline(size_t cPointNum = 3);
    
    Eigen::Array4Xd getVertices();

private:
    void            updateParams_();
    void            createControlPoints_();
    //void            updateCurve_();
    //Eigen::Vector4d bezier_(double &t, size_t first, size_t i, size_t j);
};

}

#endif
