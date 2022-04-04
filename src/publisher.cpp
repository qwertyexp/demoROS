#include "ros/ros.h"
#include "sensor_msgs/MultiDOFJointState.h"
#include "std_msgs/Header.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Wrench.h"


#include <iostream>
#include <string> // for string class



int main(int argc, char **argv) {
    ros::init(argc, argv, "talker");
    ROS_INFO_STREAM("nodeInit");
    ros::NodeHandle nh;
    ros::Publisher chatterPublisher = nh.advertise<sensor_msgs::MultiDOFJointState>("chatter", 1);
    ros::Rate loopRate(1);
    unsigned int count = 0;
    ROS_INFO_STREAM("nodeStarted");
    while (ros::ok()) {
    
        sensor_msgs::MultiDOFJointState message;
        std_msgs::Header header;
        message.header=header;
        
        std::vector<std::string> jointNames;
        std::vector<geometry_msgs::Transform> transforms;
        std::vector<geometry_msgs::Twist> twists;
        std::vector<geometry_msgs::Wrench> wrenchs;

        
        for (int i=0;i<6;i++){
            std::string jointNo=std::to_string(i);
            std::string s ("joint ");
            s+=jointNo;
            ROS_INFO_STREAM(s);
            jointNames.push_back(s);
            
            geometry_msgs::Transform transform;
            geometry_msgs::Vector3 translation;
            
            translation.x=i;
            translation.y=i;
            translation.z=i;
            geometry_msgs::Quaternion rotation;
            rotation.x=i;
            rotation.y=i;
            rotation.z=i;
            rotation.w=i;
            transform.translation=translation;
            transform.rotation=rotation;
            transforms.push_back(transform);
            
            geometry_msgs::Twist twist;
            geometry_msgs::Vector3 linear,angular;
            linear.x=i;
            linear.y=i;
            linear.z=i;
            angular.x=i;
            angular.y=i;
            angular.z=i;
            twist.linear=linear;
            twist.angular=angular;
            twists.push_back(twist);
            
            geometry_msgs::Wrench wrench;
            geometry_msgs::Vector3 force,torque;
            force.x=i;
            force.y=i;
            force.z=i;
            torque.x=i;
            torque.y=i;
            torque.z=i;
            wrench.force=force;
            wrench.torque=torque;
            wrenchs.push_back(wrench);
            
        }
        
        
        message.joint_names=jointNames;   
        message.transforms=transforms;
        message.twist=twists;
        message.wrench=wrenchs;
        
        chatterPublisher.publish(message);
        ROS_INFO_STREAM("oneCycle");
        ros::spinOnce();
        loopRate.sleep();
        count++;
    }
    return 0;
}
