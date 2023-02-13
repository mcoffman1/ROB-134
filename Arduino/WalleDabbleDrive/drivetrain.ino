//=============================Drivetrain=========================================

void forward()
{
  if (lefttick < righttick)
  {
    leftspeed = 180;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
    rightspeed = rightspeed - .01;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
  }else if (lefttick > righttick)
  {
    rightspeed = 180;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
    leftspeed = leftspeed - .01;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
  }else
  {
    leftspeed = 180;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
    rightspeed = 180;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
    //Serial.print("GO ");
  }  
}
void fullspeed()
{
   if (leftspeed != 180)
   {
     leftspeed = 180;
   }
   servo1.write(leftspeed);
   servo2.write(leftspeed);

   if (rightspeed != 180)
   {
     rightspeed = 180;
   }
   servo3.write(rightspeed);
   servo4.write(rightspeed);
}


void reverse()
{
  if (leftspeed != 0)
  {
    leftspeed = 0;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
  }
  if (rightspeed != 0)
  {
    rightspeed = 0;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
  }
}


void left()
{
  if (leftspeed != 0)
  {
    leftspeed = 0;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
  }
  if (rightspeed != 180)
  {
    rightspeed = 180;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
  }
}


void right()
{
  if (leftspeed != 180)
  {
    leftspeed = 180;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
  }
  if (rightspeed != 0)
  {
    rightspeed = 0;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
  }
}


void stopall()
{
  if (leftspeed != 90)
  {
    leftspeed = 90;
    servo1.write(leftspeed);
    servo2.write(leftspeed);
  }
  if (rightspeed != 90)
  {
    rightspeed = 90;
    servo3.write(rightspeed);
    servo4.write(rightspeed);
  }
}
