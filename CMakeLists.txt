cmake_minimum_required(VERSION 3.4)
project(MP4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

#add_compile_definitions("EIGEN_STACK_ALLOCATION_LIMIT 0")

file(GLOB ELEMENTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Elements/*.cpp )
file(GLOB NODES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Nodes/*.cpp )

add_library(ModelHierarchy STATIC ${ELEMENTS} ${NODES})
target_include_directories(ModelHierarchy PUBLIC C:/eigen-3.4.0)

add_executable(testModelHierachy testModelHierachy.cpp)
target_link_libraries(testModelHierachy PRIVATE ModelHierarchy )
