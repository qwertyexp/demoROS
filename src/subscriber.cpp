#include <iostream>
#include <string>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Header.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Wrench.h"

#include "sensor_msgs/MultiDOFJointState.h"



void chatterCallback(const sensor_msgs::MultiDOFJointState& msg)
{
    for (int i=0; i<6;i++){
        ROS_INFO("I heard: [%s]", msg.joint_names[i].c_str());
        ROS_INFO("Tranforms: [%f]", msg.transforms[i].translation.x);
        ROS_INFO("Twist: [%f]", msg.twist[i].linear.x);
        ROS_INFO("Wrench: [%f]", msg.wrench[i].force.x);
    }
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber =
    nodeHandle.subscribe("chatter",10,chatterCallback);
    ros::spin();
    return 0;
}
