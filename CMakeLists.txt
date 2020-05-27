cmake_minimum_required(VERSION 3.5)

project(witcher_bt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(BehaviorTreeV3)
find_package(Boost)
add_executable(${PROJECT_NAME} main.cpp)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

target_link_libraries(${PROJECT_NAME} BT::behaviortree_cpp_v3 ${Boost_LIBRARIES})