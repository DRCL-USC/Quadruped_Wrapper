# Quadruped Wrapper
This repository offers a wrapper for a nonlinear Model Predictive Control (MPC) controller tailored for Unitree quadruped robots. It builds upon the [legged_control](https://github.com/qiayuanl/legged_control) and [legged_perceptive_control](https://github.com/qiayuanl/legged_perceptive) repositories, which are based on [OCS2](https://leggedrobotics.github.io/ocs2/).

# Installation
## Prerequisites

The library is written in C++11 and has been tested on Ubuntu 20.04 with the library versions available in the package sources.

## Dependencies
* A C++ compiler with C++11 support
* Eigen (version 3.3)
* Boost C++ (version 1.71)
* Catkin: `sudo apt-get install catkin`
* Catkin-pkg for Python 3: `sudo apt install python3-catkin-tools`
* LCM: `sudo apt-get install liblcm-dev`
* ROS Noetic
* Additional packages: `sudo apt install liburdfdom-dev liboctomap-dev libassimp-dev libglpk-dev libmpfr-dev`
* ROS-related packages: `sudo apt install ros-noetic-pybind11-catkin ros-noetic-octomap-msgs ros-noetic-costmap-2d ros-noetic-realsense2-description`

## Build the Library

Create a new catkin workspace:
```
# Create the directories
# Do not forget to change <...> parts
mkdir -p <directory_to_ws>/<catkin_ws_name>/src
cd <directory_to_ws>/<catkin_ws_name>/

# Initialize the catkin workspace
catkin init
catkin config --extend /opt/ros/noetic
catkin config -DCMAKE_BUILD_TYPE=RelWithDebInfo
```
Clone the code:

```
# Navigate to the src directory
cd <directory_to_ws>/<catkin_ws_name>/src

# Clone the repo:
git clone --depth 1 --recurse-submodules
```
Build the package (simulation and hardware):
```
cd ..
catkin build legged_deployment
```

# Usage
## Running Simulation
To start the simulation, first launch the Gazebo world:
```
roslaunch custom_description gazebo_world.launch wname:=stairs_stepping_stone gui:=true
```
You can specify the world name with `wname` and toggle the `gui`.

Next, load the controller by launching the following file:
```
roslaunch legged_deployment load_controller.launch
```

Then, run the controller node:
```
rosrun legged_deployment controller_client_node <controller_name> start
```
For `<controller_name>`, use `perceptive_controller` for the perceptive controller or `legged_controller` for the blind controller. If using the perceptive controller, also launch the elevation map and plane segmentation nodes:
```
roslaunch legged_deployment elevation_mapping.launch rviz:=true
```
This step is not needed for the blind controller.

Finally, run the keyboard command node to control the robot with the keyboard:
```
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
Use `w` and `s` for forward and backward velocity, `a` and `d` for lateral velocity, and `g` and `h` for rotational velocity.

## Running Hardware
For hardware operation, instead of launching Gazebo, run the hardware stack:
```
roslaunch legged_unitree_hw legged_unitree_hw.launch
```
To load cameras such as t265 and d435, use the following launch file or define a custom one:
```
roslaunch custom_description unitree_hw.launch
```
The remaining steps, including loading and running the controller, are the same as for the simulation.

## Using Tmux Script 
Multiple Tmux scripts located in the `scripts` directory automate the process of running the simulation or hardware as explained above. To use these scripts, first install:
```
sudo apt-get install tmux tmuxp
```

Next, navigate to the scripts directory and load the Tmux session:
```
cd scripts
tmuxp load simulation_with_perception.yaml
```
You can modify the Tmux scripts based on your specifications.