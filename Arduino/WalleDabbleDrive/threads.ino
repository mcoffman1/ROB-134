
void tickcallback()
{
  // Serial.println("Number of Ticks: ");
  // Serial.println(right_wheel_tick_count);
  // Serial.println(left_wheel_tick_count);
  // Serial.println();
}

//===================Head Control===========================

void headcallback()
{
  Dabble.processInput();
  if (GamePad.isTrianglePressed())
  {
    if (headup)
    {
      neckbasepos = 180;
      neckbase.write(neckbasepos);
      neck2pos = 80;
      neck2.write(neck2pos);
    }
  }
  else if (GamePad.isCrossPressed())
  {
    if (headup)
    {
      neckbasepos = 80;
      neckbase.write(neckbasepos);
      neck2pos = 180;
      neck2.write(neck2pos);
    }
  }
  else if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    lookright();
  }
  else if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    lookleft();
  }
  else if (GamePad.isStartPressed())
  {
        neck2pos = 180;
        neck2.write(neck2pos);
        delay(500);
        neckbasepos = 80;
        neckbase.write(neckbasepos);
        headup = true;
        Serial.println(headup);
  }

  else if (GamePad.isSelectPressed())
  {
    //Serial.print("Select");
    if (headup)
    {
      neck2pos = 180;
      neck2.write(neck2pos);
      neckbasepos = 80;
      neckbase.write(neckbasepos);
      delay(3000);
      neck2pos = 180;
      neck2.write(neck2pos);
      neckbasepos = 0;
      neckbase.write(neckbasepos);
      headup = false;
      Serial.println(headup);
    }
  }
  else
  {
    // if (lastinput == 0)
    // {
    //   ;
    // }else
    // {
    //   stopall();
    //   lastinput = 0;
    //   //Serial.println("stop");
    // }
  }
}
    

