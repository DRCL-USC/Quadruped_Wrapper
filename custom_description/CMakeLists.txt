cmake_minimum_required(VERSION 3.10)
project(custom_description)

## Find catkin macros and libraries
find_package(catkin REQUIRED
        COMPONENTS
        )

###################################
## catkin specific configuration ##
###################################
catkin_package(
        CATKIN_DEPENDS
)

#############
## Install ##
#############

# Mark resource files for installation
install(
        DIRECTORY config launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
