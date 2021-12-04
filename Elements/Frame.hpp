#ifndef MH_FRAME
#define MH_FRAME

#include "Eigen/Dense"

namespace MH
{

class Frame
{
public:
    Frame(double x, double y);
    Frame(double x, double y, double z);

    size_t axes() const;

    double& operator()(int row, int column);
    const double& operator()(int row, int column) const;

private:
    void error_(std::string message) const;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> frame_;
};

std::ostream & operator<< (std::ostream &os, Frame const &rhs);

}

#endif
