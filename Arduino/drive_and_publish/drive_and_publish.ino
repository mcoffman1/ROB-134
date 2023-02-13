//#include <ThreadController.h>
#include <Thread.h>
#include <StaticThreadController.h>
//===================================================
#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>
//===================================================
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Servo.h>

#define ENB A1                       // definitions for ros run (not currently used)
#define ENA A2
#define IN4 5
#define IN3 6
#define IN2 11
#define IN1 12

float righteyepos = 42;               // head home position
float lefteyepos = 72;
float neck2pos = 180;                 // 180 is colapsed
float neckbasepos = 80;               // 0 is collapsed

volatile float leftspeed = 90;
volatile float rightspeed = 90;
int lastinput = 0;

bool looking = false;

Servo servo1;                         // these four are the drivetrain motors
Servo servo2;                         // 180 = full forward.  0 = full reverse
Servo servo3;                         // 90 = stop
Servo servo4;

Servo righteye;                       // servos for head and eyes
Servo lefteye;
Servo neck2;
Servo neckbase;

//=================================================

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
 
// Keep track of the number of wheel ticks
//volatile int left_wheel_tick_count = 0;
//volatile int right_wheel_tick_count = 0;
//================================================
ros::NodeHandle nh;

// Keep track of the number of wheel ticks
std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);
//================================================
 
// One-second interval for measurements
int interval = 100;
 
void setup() 
{
  // Open the serial port at 9600 bps
  Serial.begin(9600);               // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);               // Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  
  servo1.attach(53, 1000, 2000);
  servo2.attach(52, 1000, 2000);
  servo3.attach(51, 1000, 2000);
  servo4.attach(50, 1000, 2000);

  // 7 is neck joint 2. 6 is neck joint 1 aka base joint
  neck2.attach(7, 500, 2400);
  neckbase.attach(6, 500, 2400);
  righteye.attach(2);
  lefteye.attach(4);;
  
  righteye.write(righteyepos);         //set initial position to home
  lefteye.write(lefteyepos);
  neck2.write(neck2pos);
  delay(5000);
  neckbase.write(neckbasepos);

  //========================================================
 
  // Set pin states of the encoder
  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
 
  // Every time the pin goes high, this is a tick
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_tick, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_tick, RISING);

  tickthread.onRun(tickcallback);
  tickthread.setInterval(interval);
  //=========================================================
  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  //nh.subscribe(subCmdVel);
}
 
void loop() 
{
  // If one second has passed, print the number of ticks
  if (tickthread.shouldRun())
  {
    tickthread.run();
  }

//==============================================
  
  bluetooth();                          // check to see which button is pressed from dabble app on phone
  if (GamePad.isTrianglePressed() || GamePad.isCirclePressed() || GamePad.isSquarePressed() || GamePad.isCrossPressed())
  {
    righteye.write(righteyepos);          // if eye or head position has changed move to position
    lefteye.write(lefteyepos);
    headturn.write(headturnpos);
    neckmiddle.write(neckmiddlepos);
  }
}
 
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