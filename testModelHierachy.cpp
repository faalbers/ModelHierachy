
#include "ModelHierarchy.hpp"

#include <iostream>
#include <chrono>

int main()
{
    MH::ModelHierachy modelH;
    modelH.setFrameAxisY(0,-1,0);
    modelH.setFramePosition(300,300,0);

    auto chaikin = std::make_shared<MH::ChaikinCurve>();
    //auto bspline = std::make_shared<MH::BSpline>();
    //auto bsplineNode = modelH.addModel(bspline, "BSpline");

    

    //chaikin->getValue("bob");
    //chaikin->setValue("bob", 20);
    //chaikin->getPointArrayCount("bob");

    //std::cout << chaikin->getPointFromArray("cp", 3) << std::endl;

    //chaikin->getPointArray("bob");

    //chaikin->setPointInArray("cp", 2, 1,2,3);
    //std::cout << chaikin->getPointFromArray("cp", 3) << std::endl;

    //std::cout << chaikin->getPointArray("cp") << std::endl;
    /*
    for ( auto &element : chaikin->getValueNames() )
        std::cout << element << ": " << chaikin->getValue(element) << std::endl;
    for ( auto &element : chaikin->getCountNames() )
        std::cout << element << ": " << chaikin->getCount(element) << std::endl;
    for ( auto &element : chaikin->getPointArrayNames() ) {
        std::cout << element << ": " << chaikin->getPointArrayCount(element) << std::endl;
        for ( size_t i = 0; i < chaikin->getPointArrayCount(element); i++ ) {
            std::cout << "[" << i << "] "
                << chaikin->getPointFromArray(element, i) << std::endl;
        }
        std::cout << chaikin->getPointArray(element) << std::endl;
    }
    */

    //auto chaikinNode = modelH.addModel(chaikin, "Chaikin");

    //auto nodeModel = chaikinNode->getModel();

    //std::cout << chaikinNode->getTransformedVertices() << std::endl;
    //std::cout << nodeModel->getPointArray("cp") << std::endl;
    //std::cout << "Change cp count to 3\n" << std::endl;
    //nodeModel->setCount("cpnum", 3);
    //std::cout << chaikinNode->getTransformedVertices() << std::endl;
    //std::cout << nodeModel->getPointArray("cp") << std::endl;

    //modelH.printHierarchy();
    
    /*
    auto modelA = std::make_shared<MH::Model>();
    auto modelB = std::make_shared<MH::Model>();
    auto modelC = std::make_shared<MH::Model>();

    auto nodeFred = modelH.addModel(modelA, "Fred");
    auto nodeBob = modelH.addModel(modelA, "Bob", nodeFred);
    modelH.addModel(modelB, "Jef");
    auto nodeBibi = modelH.addModel(modelC, "Bibi", nodeBob);

    nodeFred->setRz(M_PI/2);
    nodeBob->setTy(1);

    std::cout << nodeBibi->getTransform() << std::endl;

    //auto bobNode = modelH.findNodePath("/World/Fred/Bob");
    //if ( bobNode != nullptr ) {
    //    std::cout << "Found: " << bobNode->pathName() << std::endl;
    //    modelH.addModel(modelC, "Bibi", bobNode);
    //}

    //modelH.printHierarchy(true);
    //modelA.reset(); modelB.reset();modelC.reset();
    modelH.printHierarchy();
    */

    /*
    MH::Frame frame(1,1,1);
    std::cout << frame;
    
    MH::Point point(1,2,3);
    std::cout << point << std::endl;

    auto nodeA = new MH::Node();
    auto nodeB = new MH::Node(nodeA);
    auto nodeC = new MH::Node(nodeA);
    auto nodeD = new MH::Node(nodeB);
    auto nodeE = new MH::Node(nodeB);
    
    //nodeA->printHierarchy();

    delete nodeB;

    //nodeA->printHierarchy();
    */

    /*
    std::cout << "LIMIT = " << EIGEN_STACK_ALLOCATION_LIMIT << std::endl;

    Eigen::Matrix4d transform;
    transform.setIdentity();
    transform.row(3) << 1, 2, 3;

    std::cout << "transform size: " << transform.size() << std::endl;
    std::cout << "transform:\n" << transform << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    long int pointNum = 10000000;
    std::shared_ptr<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> points;
    points = std::make_shared<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(pointNum,4);
    for ( long int index = 0 ; index < pointNum; index++ ) {
        points->row(index) << 6, 5, 4, 1;
    }

    auto mid = std::chrono::high_resolution_clock::now();

    *points *= transform;

    auto end = std::chrono::high_resolution_clock::now();
    auto ms_int_a = std::chrono::duration_cast<std::chrono::milliseconds>(mid - start);
    auto ms_int_b = std::chrono::duration_cast<std::chrono::milliseconds>(end - mid);
    std::cout << "\nCreate Time: " << ms_int_a.count() << "ms\n";
    std::cout << "\nProcess Time: " << ms_int_b.count() << "ms\n";

    std::cout << "points size: " << points->size() << std::endl;
    std::cout << "point.row(0):\n" << points->row(0) << std::endl;

    */
    std::cout << "Done!\n";

    return 0;
}