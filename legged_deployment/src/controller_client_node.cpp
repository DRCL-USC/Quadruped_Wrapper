
#include "ros/ros.h"
#include "controller_manager_msgs/SwitchController.h"
#include <XmlRpcValue.h>

int main(int argc, char **argv)
{
    // Initialize the ROS node
    ros::init(argc, argv, "controller_client_node");

    // Create a ROS node handle
    ros::NodeHandle nh;
    
    // Extract the controller type and start/stop command from the command-line arguments
    std::string controller_type = argv[1];
    std::string start_or_stop = argv[2];

    // Validate the start/stop command
    if (start_or_stop != "start" && start_or_stop != "stop")
    {
        ROS_ERROR("Invalid start/stop command. Use 'start' or 'stop'.");
        return 1;
    }

    XmlRpc::XmlRpcValue loaded_controller_types; // Declare the controller_map variable
    if (!nh.getParam("controllers/", loaded_controller_types))
    {
        ROS_ERROR("Failed to get controllers");
        return 1;
    }

    if (!loaded_controller_types.hasMember(controller_type))
    {
        ROS_ERROR("Invalid controller type.");
        return 1;
    }

    // Create a client for the switch_controller service
    ros::ServiceClient client = nh.serviceClient<controller_manager_msgs::SwitchController>("controller_manager/switch_controller");

    // Create a request object
    controller_manager_msgs::SwitchController srv;

    // Fill in the request fields
    if (start_or_stop == "start")
    {
        srv.request.start_controllers.push_back("controllers/" + controller_type);
        srv.request.stop_controllers.push_back("");
    }
    else if (start_or_stop == "stop")
    {
        srv.request.start_controllers.push_back("");
        srv.request.stop_controllers.push_back("controllers/" + controller_type);
    }

    srv.request.strictness = 0;
    srv.request.start_asap = false;
    srv.request.timeout = 0.0;

    // Call the service
    if (client.call(srv))
    {
        // Service call succeeded
        if (srv.response.ok)
        {
            ROS_INFO("Controller switch successful");
        }
        else
        {
            ROS_ERROR("Controller switch failed");
        }
    }
    else
    {
        // Service call failed
        ROS_ERROR("Failed to call switch_controller service");
        return 1;
    }

    return 0;
}
