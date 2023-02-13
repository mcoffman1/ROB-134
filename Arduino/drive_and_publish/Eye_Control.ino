//==================================Eye Control========================================

void lookleft()
{
  headturnpos = headturnpos-1;
  delay(30);
}


void lookright()
{
  headturnpos = headturnpos+1;
  delay(30);
}


void headforward()
{
  if (neckmiddlepos < 180)
  {
    neckmiddlepos = neckmiddlepos+1;
    delay(30);
  }
}


void headback()
{
  if (neckmiddlepos > 0)
  {
    neckmiddlepos = neckmiddlepos-1;
    delay(30);
  }
}

//======================================Select Routine==================================

void eyeroutine()
{
  int pause = 400;
  lefteye.write(82);
  delay(pause);
  righteye.write(32);
  delay(pause);
  lefteye.write(60);
  delay(pause);
  righteye.write(50);
  delay(pause);
  lefteye.write(82);
  delay(pause);
  righteye.write(32);
  delay(pause);
  lefteye.write(60);
  delay(pause);
  righteye.write(50);
  delay(pause);
  lefteye.write(82);
  righteye.write(32);
  delay(pause/2);
  lefteye.write(60);
  righteye.write(50);
  delay(pause/2);
  lefteye.write(82);
  righteye.write(32);
  delay(pause/2);
  lefteye.write(72);
  righteye.write(42);
  delay(pause/2);
}


//=================================Start Routine Hold Select to Stop=========================

void lookaround()
{
  looking = true;
  while (looking)
  {
    selectcheck();
    for (int i = 0; i < 45; i++)
    {
      selectcheck();
      lookleft();
      headturn.write(headturnpos);
    }
    delay(1000);
    
    for (int i = 0; i < 90; i++)
    {
      selectcheck();
      lookright();
      headturn.write(headturnpos);
    }
    delay(1000);
    for (int i = 0; i < 45; i++)
    {
      selectcheck();
      lookleft();
      headturn.write(headturnpos);
    }
    delay(500);
    if (righteyepos < 40)
    {
      righteyepos = 40;
      lefteyepos = 70;
    }else if (righteyepos < 50)
    {
      righteyepos = 50;
      lefteyepos = 60;
    }else if (righteyepos < 60)
    {
      righteyepos = 60;
      lefteyepos = 50;
    }else
    {
      righteyepos = 30;
      lefteyepos = 80;
    }
    righteye.write(righteyepos);
    lefteye.write(lefteyepos);
    delay(1000);
  }
  righteyepos = 42;
  lefteyepos = 72;
  righteye.write(righteyepos);
  lefteye.write(lefteyepos);
}

//=============================================Check if select has been pressed==================

void selectcheck()
{
   Dabble.processInput();
   if (GamePad.isSelectPressed())
   {
     looking = false;
   }
}
