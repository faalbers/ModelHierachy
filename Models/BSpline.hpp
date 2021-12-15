#ifndef MH_BSPLINE
#define MH_BSPLINE

#include "Model.hpp"

namespace MH
{

class BSpline : public Model
{
public:
    BSpline(size_t cPointNum = 4, size_t subdiv = 4);
    
    Eigen::Array4Xd getVertices();

private:
    void    changeParam_(std::string name) override;
    void    readParam_(std::string name) override;
    void    createControlPoints_();

    Eigen::Vector4d bezier_(double &t, Eigen::Array4Xd &vertices, size_t first, size_t i, size_t j);
};

}

#endif
