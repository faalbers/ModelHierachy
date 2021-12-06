#ifndef MH_MODEL
#define MH_MODEL

#include <string>
#include "Eigen/Dense"

namespace MH
{

class Model
{
public:
    Model();

protected:
    friend class Node;
    Eigen::Matrix<double, Eigen::Dynamic, 4> vertices_;

};

}

#endif
