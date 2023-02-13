#include <Thread.h>
#include <StaticThreadController.h>
//======================================================================
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>
//=======================================================================
#include <Servo.h>

// Handles startup and shutdown of ROS
ros::NodeHandle nh;

double linear = 0;
double angular = 0;
//=================speed of drive motors=====================================
int leftspeed = 90;
int rightspeed = 90;

Servo servo1;                         // these four are the drivetrain motors
Servo servo2;                         // 180 = full forward.  0 = full reverse
Servo servo3;                         // 90 = stop
Servo servo4;

//===================tread for publishing tick counts======================
Thread tickthread = Thread();

// Encoder output to Arduino Interrupt pin. Tracks the tick count.
#define ENC_IN_LEFT_A 20
#define ENC_IN_RIGHT_A 21
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_LEFT_B 25
#define ENC_IN_RIGHT_B 26
// True = Forward; False = Reverse
bool Direction_left = true;
bool Direction_right = true;
// Minumum and maximum values for 16-bit integers
const int encoder_minimum = -32768;
const int encoder_maximum = 32767;

int interval = 1000;

//===================publish actual velocity====================================
std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);
//==========================================================================

// Take the velocity command as input and calculate the PWM values.
void getvel(const geometry_msgs::Twist& cmdVel) {
   
  // Calculate the PWM value given the desired velocity 
  linear = cmdVel.linear.x;
  angular = cmdVel.angular.z;
 
  // Check if we need to turn 
  if (angular < 0.0) 
  {
    left();
  }else if (angular > 0.0) 
  {
    right();
  }else 
  {
    if (linear == 0)
    {
      stopall();
    }else
    {
      forward();
      right_wheel_tick_count.data = rightspeed;
    }
  } 
}

// Set up ROS subscriber to the velocity command
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &getvel );

//============================================================================
//===================SETUP====================================================
//============================================================================

void setup()
{
  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(subCmdVel);
  //===================publish for testing====================================
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  //==========================================================================
  
  servo1.attach(53, 1000, 2000);
  servo2.attach(52, 1000, 2000);
  servo3.attach(51, 1000, 2000);
  servo4.attach(50, 1000, 2000);

//=================Set pin states of the encoder===============================
  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
 
  // Every time the pin goes high, this is a tick
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_tick, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_tick, RISING);

//=====================thread setup===============================================
  tickthread.onRun(tickcallback);
  tickthread.setInterval(interval);

}

//============================================================================
//====================LOOP====================================================
//============================================================================

void loop()
{
// If one second has passed, print the number of ticks
  if (tickthread.shouldRun())
  {
    tickthread.run();
  }
  nh.spinOnce();
}

//========================calculate tick count on interupt====================

// Increment the number of ticks
void right_wheel_tick() 
{
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if(val == LOW) 
  {
    Direction_right = false; // Reverse
  }
  else 
  {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) 
  {
    if (right_wheel_tick_count.data == encoder_maximum) 
    {
      right_wheel_tick_count.data = encoder_minimum;
    }
    else 
    {
      right_wheel_tick_count.data++;  
    }    
  }
  else 
  {
    if (right_wheel_tick_count.data == encoder_minimum) 
    {
      right_wheel_tick_count.data = encoder_maximum;
    }
    else 
    {
      right_wheel_tick_count.data--;  
    }   
  }
}
 

// Increment the number of ticks
void left_wheel_tick() 
{
  // Read the value for the encoder for the left wheel
  int val = digitalRead(ENC_IN_LEFT_B);
 
  if(val == LOW) 
  {
    Direction_left = true; // Reverse
  }
  else 
  {
    Direction_left = false; // Forward
  }
   
  if (Direction_left) 
  {
    if (left_wheel_tick_count.data == encoder_maximum) {
      left_wheel_tick_count.data = encoder_minimum;
    }
    else 
    {
      left_wheel_tick_count.data++;  
    }  
  }
  else 
  {
    if (left_wheel_tick_count.data == encoder_minimum) {
      left_wheel_tick_count.data = encoder_maximum;
    }
    else 
    {
      left_wheel_tick_count.data--;  
    }   
  }
}