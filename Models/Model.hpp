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

    //std::vector<std::string>    getValueArrayNames() const;
    //size_t                      getValueArrayCount(std::string name) const;
    //void                        setValueArray(std::string name, const Eigen::Matrix<double, Eigen::Dynamic, 1> &vArray);
    void                        setValueInArray(std::string name, size_t index, double value);
    /*
    const Eigen::Matrix<double, Eigen::Dynamic, 1>
                                &getValueArray(std::string name) const;
    double                      getValueFromArray(std::string name, size_t index) const;
    */
    std::vector<std::string>    getPointArrayNames() const;
    size_t                      getPointArrayCount(std::string name) const;
    void                        setPointArray(std::string name, const Eigen::Matrix<double, Eigen::Dynamic, 4> &pArray);
    void                        setPointInArray(std::string name, size_t index, double x, double y, double z);
    const Eigen::Matrix<double, Eigen::Dynamic, 4>
                                &getPointArray(std::string name) const;
    Eigen::RowVector4d          getPointFromArray(std::string name, size_t index) const;

protected:
    friend class Node;
    void            addValue_(std::string name, double value = 0.0);
    void            addValueArray_(std::string name, size_t size, double value = 0.0);
    void            addCount_(std::string name, size_t value = 0);
    void            addPointArray_(std::string name, size_t size);
    virtual void    updateParams_() = 0;
    void            error_(std::string message) const;

    Eigen::Matrix<double, Eigen::Dynamic, 4>    vertices_;
    
    std::map<std::string, double>               values_;
    std::map<std::string, Eigen::Matrix<double, Eigen::Dynamic, 1>>
                                                valueArrays_;
    std::map<std::string, size_t>               counts_;
    std::map<std::string, Eigen::Matrix<double, Eigen::Dynamic, 4>>
                                                pointArrays_;

};

}

#endif
