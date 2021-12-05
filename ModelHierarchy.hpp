#ifndef MH_MODELHIERARCHY
#define MH_MODELHIERARCHY

#define EIGEN_STACK_ALLOCATION_LIMIT 0

//#include "Elements/Point.hpp"
//#include "Elements/PointArray.hpp"
//#include "Elements/Frame.hpp"
#include "Elements/Node.hpp"
#include "Models/Model.hpp"
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

    Node    *findNodePath(std::string nodePath);

    void    printHierarchy() const;

private:
    Node    *world_;
};

}

#endif
