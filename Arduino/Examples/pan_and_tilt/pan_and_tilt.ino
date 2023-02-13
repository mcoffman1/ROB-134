#include <Dynamixel_Servo.h>

#define HALF_DUPLEX_DIRECTION_PIN 4
servo_error_t error;

/*--------------------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
  
  servo_init(&Serial3, HALF_DUPLEX_DIRECTION_PIN, SERVO_DEFAULT_BAUD);
}

/*--------------------------------------------------------------------*/
void loop(void)
{
//  using high-level interface
//  4 = look up 2.5 = home
  error = servo_set(1, SERVO_REGISTER_GOAL_ANGLE, 2.25, 50);
  delay(1000);
  
//  using high-level interface
//  5 = look left 3.25 = home
  error = servo_set(2, SERVO_REGISTER_GOAL_ANGLE, 3.25, 50);
  delay(1000);
}

//============================SERIAL EVENTS============================

void serialEvent()
{
  delay(50);
  while (Serial.available())
  {
    Serial.println(Serial.read());
  }
  //complete = !complete;
  //Serial.println(complete);
}
