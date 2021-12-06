#ifndef MH_NODE
#define MH_NODE

#include <string>
#include <set>
#include <memory>
#include "../Models/Model.hpp"
#include "Eigen/Dense"

namespace MH
{

class Node
{
public:
    Node(std::string name, std::shared_ptr<Model> model, Node *parent = nullptr);
    ~Node();

    std::string pathName() const;
    void        printHierarchy(bool data = false) const;
    Node        *findNodePath(std::string nodePath);

    void        setTx(double x);
    void        setTy(double y);
    void        setTz(double z);
    void        setRx(double x);
    void        setRy(double y);
    void        setRz(double z);
    void        setSx(double x);
    void        setSy(double y);
    void        setSz(double z);

    Eigen::Matrix4d getTransform() const;

private:
    void        pathName_(std::string &pathName) const;
    void        setTransform_();
    void        getTransform_(Eigen::Matrix4d &transform) const;

    std::string             name_;
    Node                    *parent_;
    std::set<Node *>        children_;
    std::shared_ptr<Model>  model_;
    Eigen::Matrix4d         frame_;
    double                  tx_, ty_, tz_, rx_, ry_, rz_, sx_, sy_, sz_;
    Eigen::Matrix4d         transform_;
};

}

#endif
