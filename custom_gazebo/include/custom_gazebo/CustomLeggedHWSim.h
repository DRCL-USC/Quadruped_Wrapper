#pragma once

#include <deque>
#include <unordered_map>

#include <gazebo_ros_control/default_robot_hw_sim.h>
#include <hardware_interface/imu_sensor_interface.h>
#include <hardware_interface/joint_command_interface.h>

#include <legged_common/hardware_interface/ContactSensorInterface.h>
#include <legged_common/hardware_interface/HybridJointInterface.h>

#include <legged_gazebo/LeggedHWSim.h>

namespace legged {

class CustomLeggedHWSim : public gazebo_ros_control::DefaultRobotHWSim {
 public:
  bool initSim(const std::string& robot_namespace, ros::NodeHandle model_nh, gazebo::physics::ModelPtr parent_model,
               const urdf::Model* urdf_model, std::vector<transmission_interface::TransmissionInfo> transmissions) override;
  void readSim(ros::Time time, ros::Duration period) override;
  void writeSim(ros::Time time, ros::Duration period) override;

 private:
  void parseImu(XmlRpc::XmlRpcValue& imuDatas, const gazebo::physics::ModelPtr& parentModel);
  void parseContacts(XmlRpc::XmlRpcValue& contactNames);

  HybridJointInterface hybridJointInterface_;
  ContactSensorInterface contactSensorInterface_;
  hardware_interface::ImuSensorInterface imuSensorInterface_;

  gazebo::physics::ContactManager* contactManager_{};

  std::list<HybridJointData> hybridJointDatas_;
  std::list<ImuData> imuDatas_;
  std::unordered_map<std::string, std::deque<HybridJointCommand> > cmdBuffer_;
  std::unordered_map<std::string, bool> name2contact_;

  double delay_{};
  gazebo::physics::ModelPtr parent_model_;
};

}  // namespace legged
