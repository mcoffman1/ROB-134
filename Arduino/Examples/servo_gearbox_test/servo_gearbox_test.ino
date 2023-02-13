/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo neck2;                           // create servo object to control a servo
Servo neckbase;
Servo righteye;
Servo lefteye;

float righteyepos = 42;               // head home position
float lefteyepos = 72;
float neck2pos = 180;                 // 180 is colapsed
float neckbasepos = 80;               // 0 is collapsed
bool headup = true;

bool complete = 0;

void setup() 
{
  Serial.begin(9600);
  // 7 is neck joint 2. 6 is neck joint 1 aka base joint
  neck2.attach(7, 500, 2400);
  neckbase.attach(6, 500, 2400);
  righteye.attach(2);
  lefteye.attach(4);

  righteye.write(righteyepos);
  lefteye.write(lefteyepos);
  neck2.write(neck2pos);
  delay(5000);
  neckbase.write(neckbasepos);
}

//==========================================================

void loop(void)
{
  ;
}

//============================SERIAL EVENTS============================

void serialEvent()
{
  delay(50);
  while (Serial.available())
  {
    int inbyte = Serial.read();
    //Serial.println(inbyte);
    if (inbyte == 32)
    {
      //Serial.print("DID IT");
      if (complete)
      {
        neck2pos = 180;
        neck2.write(neck2pos);
        neckbasepos = 80;
        neckbase.write(neckbasepos);
        headup = true;
      }else
      {
        neck2pos = 180;
        neck2.write(neck2pos);
        neckbasepos = 0;
        neckbase.write(neckbasepos);
        headup = false;
      }
    }else if (inbyte == 119 && headup)
    {
        neckbasepos = 180;
        neckbase.write(neckbasepos);
        neck2pos = 80;
        neck2.write(neck2pos);
    }else if (inbyte == 115 && headup)
    {
        neckbasepos = 80;
        neckbase.write(neckbasepos);
        neck2pos = 180;
        neck2.write(neck2pos);
    }
  }
  complete = !complete;
  //Serial.println(complete);
}
