//===================================Bluetooth Run=====================================

void bluetooth()
{
  Dabble.processInput();
  
  if (GamePad.isUpPressed())
  {
    if (lastinput == 1)
    {
      ;
    }else
    {
      forward();
      lastinput = 1;
      //Serial.print("UP");
    }
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
  else if (GamePad.isTrianglePressed())
  {
    //Serial.print("Triangle");
    headforward();
  }
  else if (GamePad.isCrossPressed())
  {
    //Serial.print("Cross");
    headback();
  }
  else if (GamePad.isCirclePressed())
  {
    //Serial.print("Circle");
    lookright();
  }
  else if (GamePad.isSquarePressed())
  {
    //Serial.print("Square");
    lookleft();
  }
  else if (GamePad.isStartPressed())
  {
    //Serial.print("Start");
    lookaround();
  }

  else if (GamePad.isSelectPressed())
  {
    //Serial.print("Select");
    eyeroutine();
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
      //Serial.println("stop");
    }
  }
}
