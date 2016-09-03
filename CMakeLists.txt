cmake_minimum_required(VERSION 2.8.3)
project(colegobot)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  std_msgs
  geometry_msgs
)

catkin_package()

## Build node
add_executable(pose_broadcaster src/pose_broadcaster.cpp)
target_link_libraries(pose_broadcaster ${catkin_LIBRARIES})
add_dependencies(pose_broadcaster colegobot_gencpp)
