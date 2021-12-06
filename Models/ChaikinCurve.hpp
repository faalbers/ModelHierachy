#ifndef MH_CHAIKINCURVE
#define MH_CHAIKINCURVE

#include "Model.hpp"

namespace MH
{

class ChaikinCurve : public Model
{
public:
    ChaikinCurve(size_t cPointNum = 4, size_t recursions = 4);

    void setControlPointNum(size_t controlPointNum);
    void setControlPoint(size_t index, double x, double y, double z);
    void setControlPointX(size_t index, double val);
    void setControlPointY(size_t index, double val);
    void setControlPointZ(size_t index, double val);

    Eigen::Matrix<double, Eigen::Dynamic, 4> getControlPoints() const;

private:
    size_t  vertexCount_(size_t cPointNum, size_t recursions) const;
    void    updateControlPoints_();
    void    updateCurve_();
    size_t  chaikinAlgorthm_(
                Eigen::Matrix<double, Eigen::Dynamic, 4> &tempVertices,
                size_t tempCount);

    size_t                                      controlPointNum_;
    size_t                                      recursions_;
    Eigen::Matrix<double, Eigen::Dynamic, 4>    controlPoints_;
};

}

#endif
