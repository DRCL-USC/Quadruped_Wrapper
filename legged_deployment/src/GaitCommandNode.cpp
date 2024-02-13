#include <ros/init.h>
#include <ros/package.h>

#include "legged_deployment/GaitPublisher.h"

using namespace legged;

int main(int argc, char* argv[]) {
  const std::string robotName = "legged_robot";

  // Initialize ros node
  ros::init(argc, argv, robotName + "_mpc_mode_schedule");
  ros::NodeHandle nodeHandle;
  // Get node parameters
  std::string gaitCommandFile;
  nodeHandle.getParam("gaitCommandFile", gaitCommandFile);
  std::cerr << "Loading gait file: " << gaitCommandFile << std::endl;

  GaitPublisher gaitCommand(nodeHandle, gaitCommandFile, robotName, true);

  ros::spin();

  // Successful exit
  return 0;
}