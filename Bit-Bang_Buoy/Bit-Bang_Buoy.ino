//Driver pins
int dir1 = 5;
int step1 = 6;
int dir2 = 7;
int step2 = 8;
int dir3 = 9;
int step3 = 10;
int dir4 = 11;
int step4 = 12;

int st = 1000;

//time variables
double timeNow;
double indexOn;
double indexOff;

//Sensor variables
int pinS1 = 5;
int dataS1 = 0;
int detectS1 = 421;

int pinS2 = 4;
int dataS2 = 0;
int detectS2 = 425;

//Calibration variables
  byte cBanner = 0;

  int extSpeed = st*2;
  int intSpeed = extSpeed/20;

  byte motorBanner1 = 0;
  byte motorBanner2 = 0;

  double indexRead;
  double readInterval = 20000;//twenty times per second

  double indexOnExt = timeNow + extSpeed;
  double indexOffExt = indexOnExt + extSpeed;
  double indexOnInt = timeNow + intSpeed;
  double indexOffInt = indexOnInt + intSpeed;

  double indexOnExt2 = timeNow + extSpeed;
  double indexOffExt2 = indexOnExt2 + extSpeed;
  double indexOnInt2 = timeNow + intSpeed;
  double indexOffInt2 = indexOnInt2 + intSpeed;

  int stepCounter = 0;

  double stickOffTime = 2500000;
  double indexStickOff;

void setup() 
{
  Serial.begin (2000000);
  Serial.println ("inicio");
  setModes ();
  setInitials ();

  timeNow = micros ();
  calibrationRoutine ();
  int ddd = 9;
  while (ddd > 0)
  {
  twoLevelStepCounter ();
  ddd--;
  }
}

void loop() 
{
  //Serial.println ("loop");
  timeNow = micros ();
  runAll ();

}
