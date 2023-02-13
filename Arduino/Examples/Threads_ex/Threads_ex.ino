
#include <Thread.h>
int ledPin = 13;

volatile int x = 0;

//My simple Thread
Thread myThread = Thread();
Thread otherthread = Thread();

void setup(){
	Serial.begin(9600);

	pinMode(ledPin, OUTPUT);

	myThread.onRun(thread);
	//myThread.setInterval(2000);

  otherthread.onRun(thread2);
  //otherthread.setInterval(1000);
  
}

void loop(){
	// checks if thread should run
	if(myThread.shouldRun())
		myThread.run();
  if (otherthread.shouldRun())
  {
    otherthread.run();
  }
	// Other code...
	x = x + 1;
  delay(500);
}

//==========================================================================

// callback for myThread
void thread(){
  static bool ledStatus = false;
  ledStatus = !ledStatus;

  digitalWrite(ledPin, ledStatus);

  Serial.print("COOL! I'm running on: ");
  Serial.println(millis());
}

void thread2()
{
  Serial.print("THREAD TWO WORKS TOO!   ");
  Serial.println(x);
}