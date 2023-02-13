#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>

// Handles startup and shutdown of ROS
ros::NodeHandle nh;

double linear = 0;
double angular = 0;

//===================publish for testing====================================
std_msgs::Int16 velpub;
ros::Publisher cmdvelpub("vel_pub", &velpub);
//==========================================================================

// Take the velocity command as input and calculate the PWM values.
void getvel(const geometry_msgs::Twist& cmdVel) {
   
  // Calculate the PWM value given the desired velocity 
  linear = cmdVel.linear.x;
  angular = cmdVel.angular.z;
 
  // Check if we need to turn 
  if (cmdVel.angular.z != 0.0) 
  {
    velpub.data = angular;
  }
  // Go straight
  else 
  {
    velpub.data = linear;
  } 
}

// Set up ROS subscriber to the velocity command
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &getvel );

//============================================================================
//===================SETUP====================================================
//============================================================================

void setup()
{
  //Serial.begin(115200);
  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(subCmdVel);
  //===================publish for testing====================================
  nh.advertise(cmdvelpub);
  //==========================================================================
}

//============================================================================
//====================LOOP====================================================
//============================================================================

void loop()
{
  //===================publish for testing====================================
  cmdvelpub.publish( &velpub );
  delay(500);
  //==========================================================================
  nh.spinOnce();
  //calc_pwm_values();
}