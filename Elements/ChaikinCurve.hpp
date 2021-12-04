#ifndef MH_CHAIKINCURVE
#define MH_CHAIKINCURVE

#include "Point.hpp"
#include <vector>

namespace MH
{

class ChaikinCurve
{
public:
    ChaikinCurve();
    
    std::vector<Point> controlPoints;
};

}

#endif
