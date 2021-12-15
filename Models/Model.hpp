#ifndef MH_MODEL
#define MH_MODEL

#include <string>
#include <map>
#include <memory>
#include "Eigen/Dense"

namespace MH
{

class Model
{
public:
    Model();

    std::vector<std::string>    getValueNames() const;
    void                        setValue(std::string name, double value);
    const double                &getValue(std::string name) const;

    std::vector<std::string>    getCountNames() const;
    void                        setCount(std::string name, size_t value);
    const size_t                &getCount(std::string name) const;

    std::vector<std::string>    getMatrixNames() const;
    void                        setMatrix(std::string name, Eigen::Matrix4d value);
    const Eigen::Matrix4d       &getMatrix(std::string name) const;

    std::vector<std::string>    getValueArrayNames() const;
    size_t                      getValueArrayCount(std::string name) const;
    void                        setValueArray(std::string name, Eigen::ArrayXd &vArray);
    void                        setValueInArray(std::string name, size_t index, double value);
    const Eigen::ArrayXd        &getValueArray(std::string name) const;
    double                      getValueFromArray(std::string name, size_t index) const;

    std::vector<std::string>    getPointArrayNames() const;
    size_t                      getPointArrayCount(std::string name) const;
    void                        setPointArray(std::string name, const Eigen::Array4Xd &pArray);
    void                        setPointInArray(std::string name, size_t index, double x, double y, double z);
    void                        setPointInArray(std::string name, size_t index, Eigen::Vector4d);
    const Eigen::Array4Xd       &getPointArray(std::string name) const;
    Eigen::Vector4d             getPointFromArray(std::string name, size_t index) const;

    virtual Eigen::Array4Xd     getVertices() = 0;

protected:
    friend class Node;
    void            addValue_(std::string name, double value = 0.0);
    void            addValueArray_(std::string name, size_t size, double value = 0.0);
    void            addCount_(std::string name, size_t value = 0);
    void            addPointArray_(std::string name, size_t pointCount = 0);
    virtual void    changeParam_(std::string name) = 0;
    virtual void    readParam_(std::string name) = 0;
    void            error_(std::string message) const;

    std::map<std::string, double>               values_;
    std::map<std::string, Eigen::ArrayXd>       valueArrays_;
    std::map<std::string, size_t>               counts_;
    std::map<std::string, Eigen::Array4Xd>      pointArrays_;
    std::map<std::string, Eigen::Matrix4d>      matrices_;
};

}

#endif
