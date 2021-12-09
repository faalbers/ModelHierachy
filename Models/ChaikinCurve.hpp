#ifndef MH_CHAIKINCURVE
#define MH_CHAIKINCURVE

#include "Model.hpp"

namespace MH
{

class ChaikinCurve : public Model
{
public:
    ChaikinCurve(size_t cPointNum = 4, size_t recursions = 4);

private:
    size_t  vertexCount_(size_t cPointNum, size_t recursions) const;
    void    updateParams_();
    void    updateControlPoints_();
    void    updateCurve_();
    size_t  chaikinAlgorthm_(
                Eigen::Array4Xd &tempVertices,
                size_t tempCount);
};

}

#endif
