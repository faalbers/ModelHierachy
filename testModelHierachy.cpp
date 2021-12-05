
#include "ModelHierarchy.hpp"

#include <iostream>
#include <chrono>
#include <memory>

int main()
{
    MH::Frame frame(1,1,1);
    std::cout << frame;
    
    MH::Point point(1,2,3);
    std::cout << point << std::endl;

    auto nodeA = new MH::Node("Fred");
    auto nodeB = new MH::Node("Bob",nodeA);
    auto nodeC = new MH::Node("Jef",nodeA);
    auto nodeD = new MH::Node("Jim",nodeB);
    auto nodeE = new MH::Node("John",nodeB);
    
    nodeA->printHierarchy();

    delete nodeB;

    nodeA->printHierarchy();

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

    std::cout << "Done\n";
    */
    return 0;
}