cmake_minimum_required(VERSION 3.4)
project(MP4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(EIGEN_INCLUDE ~frank/eigen-3.4.0)
#set(EIGEN_INCLUDE C:/eigen-3.4.0)

#add_compile_definitions("EIGEN_STACK_ALLOCATION_LIMIT 0")

file(GLOB ELEMENTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Elements/*.cpp )
file(GLOB MODELS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Models/*.cpp )

add_library(ModelHierarchy STATIC ${ELEMENTS} ${MODELS} ModelHierarchy.cpp)
#target_include_directories(ModelHierarchy PUBLIC C:/eigen-3.4.0 ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ModelHierarchy PUBLIC ${EIGEN_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(testModelHierachy testModelHierachy.cpp)
target_link_libraries(testModelHierachy PRIVATE ModelHierarchy )
