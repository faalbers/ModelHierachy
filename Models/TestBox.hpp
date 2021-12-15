#ifndef MH_TESTBOX
#define MH_TESTBOX

#include "Model.hpp"

namespace MH
{

class TestBox : public Model
{
public:
    TestBox();

private:
    void    changeParam_(std::string name) override;
    void    readParam_(std::string name) override;
};

}

#endif
