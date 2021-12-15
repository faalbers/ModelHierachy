#ifndef MH_CHAIKINCURVE
#define MH_CHAIKINCURVE

#include "Model.hpp"

namespace MH
{

class ChaikinCurve : public Model
{
public:
    ChaikinCurve(size_t cPointNum = 4, size_t dubdiv = 4);

private:
    void    changeParam_(std::string name) override;
    void    readParam_(std::string name) override;
    void    createControlPoints_();
    void    updateVtx();

    size_t  vertexCount_(size_t cPointNum, size_t subdiv) const;
    size_t  chaikinAlgorithm_(size_t tempCount);
    
    bool    doVtxUpdate_; // status of vtx recalculation
};

}

#endif
