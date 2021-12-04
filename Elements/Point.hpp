#ifndef MH_POINT
#define MH_POINT

#include "Eigen/Dense"

namespace MH
{

class Point
{
public:
    Point(double x, double y);
    Point(double x, double y, double z);

    size_t axes() const;

    double& operator()(int index);
    const double& operator()(int index) const;

private:
    void error_(std::string message) const;

    Eigen::RowVector<double, Eigen::Dynamic> point_;
};

std::ostream & operator<< (std::ostream &os, Point const &rhs);

}

#endif
