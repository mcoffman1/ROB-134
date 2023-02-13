//===================================Bluetooth Run=====================================

void bluetooth()
{
  Dabble.processInput();
  
  if (GamePad.isUpPressed())
  {
    if (lastinput == 1)
    {
      forward();
    }else
    {
      fullspeed();
      lastinput = 1;
      lefttick = righttick;
      //Serial.print("lastinput: "); Serial.println(lastinput);
    }//delay(50);
  }


  else if (GamePad.isDownPressed())
  {
    if (lastinput == 2)
    {
      ;
    }else
    {
      reverse();
      lastinput = 2;
      //Serial.print("DOWN");
    }
  }

  else if (GamePad.isLeftPressed())
  {
    if (lastinput == 3)
    {
      ;
    }else
    {
      left();
      lastinput = 3;
      //Serial.print("Left");
    }
  }

  else if (GamePad.isRightPressed())
  {
    if (lastinput == 4)
    {
      ;
    }else
    {
      right();
      lastinput = 4;
      //Serial.print("Right");
    }
  }

  else
  {
    if (lastinput == 0)
    {
      ;
    }else
    {
      stopall();
      lastinput = 0;
      Serial.println("stop");
    }
  }
}
