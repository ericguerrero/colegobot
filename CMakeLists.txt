cmake_minimum_required(VERSION 2.8.3)
project(colegobot)

## Find catkin macros and libraries
find_package(catkin REQUIRED
  roscpp
  rospy
  tf
  std_msgs
  nav_msgs
  geometry_msgs)

catkin_package(CATKIN_DEPENDS
  roscpp
  rospy
  tf
  std_msgs
  nav_msgs
  geometry_msgs)


## Build node
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(pose_broadcaster src/pose_broadcaster.cpp)
target_link_libraries(pose_broadcaster ${catkin_LIBRARIES})
add_dependencies(pose_broadcaster ${catkin_EXPORTED_TARGETS})
