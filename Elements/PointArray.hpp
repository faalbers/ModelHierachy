#ifndef MH_POINTARRAY
#define MH_POINTARRAY

#include "Point.hpp"

namespace MH
{

class PointArray
{

public:
    PointArray(size_t pointsNum);

private:
    Eigen::Matrix<double, Eigen::Dynamic, 4> points_;
};

}

#endif
