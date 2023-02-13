/*
 This program is the interpretation routine of standard output protocol of TFmini-Plus product on Arduino.
 For details, refer to Product Specifications.
 For Arduino boards with only one serial port like UNO board, the function of software visual serial port is
to be used.
*/
//#include <SoftwareSerial.h> //header file of software serial port
//SoftwareSerial mySerial(28,30); //define software serial port name as Serial3 and define pin28 as RX and pin30 as TX

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and
directly use Serial3 serial port*/
#include <Thread.h>
Thread mythread = Thread();

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
float temprature;
int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package

bool pincheck = false;

void setup() 
{
  pinMode(8,INPUT_PULLUP);
  pinMode(27,OUTPUT);
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino

  mythread.onRun(mythreadcallback);
  mythread.setInterval(2000);
}
void loop() 
{
  if (mythread.shouldRun())
  {
    mythread.run();
  }
  //serialEvent1();
}

//========================================================================================

void serialEvent1()
{
  delay(50);
  if (Serial1.available())
  { //check if serial port has data input
    //Serial.println(mySerial.read());
    if(Serial1.read() == HEADER) 
    { //assess data package frame header 0x59
      uart[0]=HEADER;
      if (Serial1.read() == HEADER) 
      { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) 
        { //save data in array
          uart[i] = Serial1.read();
        }
          dist = (uart[2] + uart[3] * 256)/2.54; //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
          temprature = uart[6] + uart[7] *256;//calculate chip temprature
          temprature = temprature/8 - 256;
        if (dist > 1000 || dist < 1)
        {
          ;
        }else
        {
          Serial.print("dist = ");
          Serial.print(dist); //output measure distance value of LiDAR
          Serial.print('\t');

          Serial.print("strength = ");
          Serial.print(strength); //output signal strength value
          Serial.print("\t Chip Temprature = ");
          Serial.print(temprature);
          Serial.println(" celcius degree"); //output chip temperature of Lidar
        }
        }
      }
    }
  }

  //===================================================================================

  void mythreadcallback()
  {
    pincheck = !pincheck;
    if (pincheck)
    {
      digitalWrite(27,HIGH);
    }else
    {
      digitalWrite(27,LOW);
    }
  }
