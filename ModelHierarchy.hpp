#ifndef MH_MODELHIERARCHY
#define MH_MODELHIERARCHY

#define EIGEN_STACK_ALLOCATION_LIMIT 0

#include "Elements.hpp"
#include "Models.hpp"
#include <string>
#include <memory>

namespace MH
{

class ModelHierachy
{
public:
    ModelHierachy();
    ~ModelHierachy();

    Node    *addModel(std::shared_ptr<Model> model, std::string name, Node *parentNode = nullptr);
    Node    *addParent(std::string name, Node *parentNode = nullptr);

    Node    *findNodePath(std::string nodePath);

    void    printHierarchy(bool data = false) const;

    static Eigen::Matrix4d  screenTransform(int width, int height);
    static Eigen::Array4Xd  pointsToScreen(Node *modelNode, Node *cameraNode, std::string pointsName);
    static void             screenToPoints(
                                Node *modelNode, Node *cameraNode,
                                std::string pointsName, Eigen::Array4Xd points);
    static void             screenToPoint(
                                Node *modelNode, Node *cameraNode,
                                std::string pointsName, size_t pointIndex, Eigen::Vector4d point);

    void    setFrameAxisX(double x, double y, double z);
    void    setFrameAxisY(double x, double y, double z);
    void    setFrameAxisZ(double x, double y, double z);
    void    setFramePosition(double x, double y, double z);

private:
    static void error_(std::string message);
    
    Node        *world_;
};

}

#endif
