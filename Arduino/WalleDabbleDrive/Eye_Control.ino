//==================================Eye Control========================================

void lookleft()
{
  //headturnpos = headturnpos-1;
  delay(30);
}


void lookright()
{
  //headturnpos = headturnpos+1;
  delay(30);
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



//=============================================Check if select has been pressed==================

// void selectcheck()
// {
//    Dabble.processInput();
//    if (GamePad.isSelectPressed())
//    {
//      looking = false;
//    }
// }
