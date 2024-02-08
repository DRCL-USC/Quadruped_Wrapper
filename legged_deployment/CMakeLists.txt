cmake_minimum_required(VERSION 3.10)
project(legged_deployment)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED
        COMPONENTS
        legged_controllers
        legged_unitree_description
        legged_perceptive_description
        legged_perceptive_controllers
        elevation_mapping
        elevation_mapping_demos
        custom_description
        teleop_twist_keyboard

        # hardware only
        legged_unitree_hw

        # Simulation only
        custom_gazebo
        realsense_gazebo_plugin
        )

catkin_package(
        INCLUDE_DIRS
        include
        LIBRARIES
        ${PROJECT_NAME}
        CATKIN_DEPENDS
        legged_controllers
        legged_unitree_description
        legged_perceptive_description
        legged_perceptive_controllers
        elevation_mapping
        elevation_mapping_demos
        custom_description

        # hardware only
        legged_unitree_hw

        # Simulation only
        custom_gazebo
        realsense_gazebo_plugin
)

###########
## Build ##
###########

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${pinocchio_INCLUDE_DIRS}
)

link_directories(
        ${pinocchio_LIBRARY_DIRS}
)

# Add your source files here
add_library(${PROJECT_NAME}
        src/GaitPublisher.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${catkin_LIBRARIES}
        ${pinocchio_LIBRARIES}
        )

target_compile_options(${PROJECT_NAME} PUBLIC ${OCS2_CXX_FLAGS})

# Add the executable
add_executable(controller_client_node src/controller_client_node.cpp)
add_dependencies(controller_client_node ${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
target_link_libraries(controller_client_node ${PROJECT_NAME} ${catkin_LIBRARIES})
target_compile_options(controller_client_node PRIVATE ${OCS2_CXX_FLAGS})

add_executable(gait_command_node src/GaitCommandNode.cpp)
add_dependencies(gait_command_node ${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
target_link_libraries(gait_command_node ${PROJECT_NAME} ${catkin_LIBRARIES})
target_compile_options(gait_command_node PRIVATE ${OCS2_CXX_FLAGS})

# Target trajectories publish node
add_executable(CmdPublisher
        src/CmdPublisher.cpp
        )
target_link_libraries(CmdPublisher
        ${catkin_LIBRARIES}
        )
        
#########################
###   CLANG TOOLING   ###
#########################
find_package(cmake_clang_tools QUIET)
if (cmake_clang_tools_FOUND)
    message(STATUS "Run clang tooling for target " ${PROJECT_NAME})
    add_clang_tooling(
            TARGETS ${PROJECT_NAME} legged_target_trajectories_publisher
            SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include
            CT_HEADER_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
            CF_WERROR
    )
endif (cmake_clang_tools_FOUND)

#############
## Install ##
#############

# Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        )

# Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        )
