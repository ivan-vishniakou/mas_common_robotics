cmake_minimum_required(VERSION 2.8.3)
project(mcr_twist_limiter)

find_package(catkin REQUIRED
  COMPONENTS
    rospy
)

catkin_python_setup()

catkin_package(
  CATKIN_DEPENDS
    rospy
    std_msgs
    geometry_msgs
)

install(PROGRAMS
  ros/scripts/twist_limiter_node
  ros/scripts/simulated_twist_gui_node
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

### TESTS
if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  find_package(rostest REQUIRED)

  roslaunch_add_file_check(ros/launch)
  add_rostest(ros/launch/twist_limiter.test)
  catkin_add_nosetests(common/test/limiter_unittest.py)
endif()
