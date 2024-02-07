cmake_minimum_required(VERSION 3.10)
project(fieldai_legged_perceptive_controllers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED
        COMPONENTS
        roscpp
        controller_interface
        legged_perceptive_interface
        legged_controllers
        grid_map_ros
        ocs2_legged_robot_ros
        )

catkin_package(
        INCLUDE_DIRS
        include
        LIBRARIES
        ${PROJECT_NAME}
        CATKIN_DEPENDS
        roscpp
        controller_interface
        legged_perceptive_interface
        legged_controllers
        grid_map_ros
        ocs2_legged_robot_ros
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${pinocchio_INCLUDE_DIRS}
)

link_directories(
        ${pinocchio_LIBRARY_DIRS}
)

# Add your source files here
file(GLOB_RECURSE SRC_LIST
    "src/GaitPublisher.cpp"
)
# Add the executable
add_executable(controller_client_node src/controller_client_node.cpp)
target_link_libraries(controller_client_node ${catkin_LIBRARIES})

add_executable(gait_command_node src/GaitCommandNode.cpp ${SRC_LIST})
target_link_libraries(gait_command_node ${catkin_LIBRARIES})

# Target trajectories publish node
add_executable(CmdPublisher
        src/CmdPublisher.cpp
        )
target_link_libraries(CmdPublisher
        ${catkin_LIBRARIES}
        )


#############
## Install ##
#############

# Mark resource files for installation
install(
        DIRECTORY meshes urdf launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
