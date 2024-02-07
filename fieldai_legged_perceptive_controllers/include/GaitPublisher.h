#pragma once

#include <string>
#include <vector>

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

#include <ocs2_legged_robot/gait/ModeSequenceTemplate.h>

namespace legged{
using namespace ocs2;
using namespace legged_robot;

/** This class implements ModeSequence communication using ROS. */
class GaitPublisher {
 public:
  GaitPublisher(ros::NodeHandle nodeHandle, const std::string& gaitFile, const std::string& robotName, bool verbose = false);

 private:
  /** Prints the list of available gaits. */
  void printGaitList(const std::vector<std::string>& gaitList) const;
  void gaitCallback(const std_msgs::String::ConstPtr& msg);

  std::vector<std::string> gaitList_;
  std::map<std::string, ModeSequenceTemplate> gaitMap_;

  ros::Publisher modeSequenceTemplatePublisher_;
  ros::Subscriber gaitsub;
};

}  // namespace legged