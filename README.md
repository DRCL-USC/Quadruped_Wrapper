# Legged Deployment


## Installation

### Install dependencies
```
sudo apt install liburdfdom-dev liboctomap-dev libassimp-dev libglpk-dev libmpfr-dev python3-catkin-tools liblcm-dev ros-noetic-pybind11-catkin ros-noetic-octomap-msgs ros-noetic-costmap-2d ros-noetic-realsense2-description
```

### Source code
The source code is hosted on Github: [Mohssen-sm/legged_deployment](https://github.com/Mohssen-sm/legged_deployment)
```
cd src
git clone --recurse-submodules https://github.com/Mohssen-sm/legged_deployment.git
```

### Build
```
cd ..
catkin config -DCMAKE_BUILD_TYPE=RelWithDebInfo
catkin build legged_deployment 
```
