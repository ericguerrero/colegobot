
## Add Packages
```
$ cd ~/ros_catkin_ws
$ rosinstall_generator ros_comm PACKAGE_NAME1 PACKAGE_NAME2  --rosdistro kinetic --deps --wet-only --tar > kinetic-custom_ros.rosinstall
```
You may keep listing as many ROS packages as you'd like separated by spaces.

Next, update the workspace with wstool:
```
$ wstool merge -t src kinetic-custom_ros.rosinstall
$ wstool update -t src
```
After updating the workspace, you may want to run rosdep to install any new dependencies that are required:

Raspbian Jessie:
```
$ rosdep install --from-paths src --ignore-src --rosdistro kinetic -y -r --os=debian:jessie
```
Finally, now that the workspace is up to date and dependencies are satisfied, rebuild the workspace:
```
$ sudo ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release --install-space /opt/ros/kinetic
```