/*
   Ivan Abreu Studio.

   26/3/2018. México City.

   This code drives a mechanism that simulate sea waves, it has 4
   stepper motors with TB6600 micro stepper driver.

   The code was rewriten to work with no libraries because they
   fail at guarantee synchronicity and precise angle control.

   This code use bitbang control, which means it works with HIGH-LOW
   toggle on every driver pin. Time is controled independently with
   micros function.

   A golden combo generator was adder. It consist on a system that receives
   only a 3-digit number via serial port. Hundreds specify the speed of
   the system in a fixed windows from 1500 to 3000 milliseconds per step.
   Tents specify the extension of every arm, which goes from 0 to 100 percent
   extension. Ones determines the slope between arms in a fixed range from
   30 to 120 degree relatives to de sensor position. A calculation is
   performed in order to get the numbers every time with memory saving
   purposes.

   Changelog

   V9.2.1 Speed adjustents
   V9.2 BT monitoring
   V9.1.2 pinout fixed to BT version
   V9.1.1 Manual calibration command added
   V9.1 Golden path generator added
   V9.0 BitBang asynchronous internal driver added
   
   This version its kind of half way. Next topics are intendeed to be developed:

   -Always calibrating routine
   -Real time data extract from WW3 algorithm
   -Unify variable map in getwaves and calibration sequences 2 & 3

   Team:

   Iván Abreu Ochoa
   Malitzin Cortez
   Beto Olguin
   Hugo Vargas
*/
//Libraries
#include <SoftwareSerial.h>//Serial library

//Objects
SoftwareSerial BT1 (4,3); //rx, tx


//

//Driver pins
int dir1 = 6;
int step1 = 5;
int dir2 = 8;
int step2 = 7;
int dir3 = 9;
int step3 = 10;
int dir4 = 11;
int step4 = 12; 

int st =10000;//<--speed change required

//time variables
double timeNow;
double timeLast;
double indexOn;
double indexOff;

//Sensor variables
int pinS1 = A0;
int dataS1 = 0;
int detectS1 = 520;//nc 605, cc535

int pinS2 = A1;
int dataS2 = 0;
int detectS2 = 550;//nc 635, cc550

//Calibration variables
byte cBanner = 0;

int extSpeed = st;
int intSpeed = extSpeed / 35;

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

double stickOffTime = 2500000;//Time of ahead start, needed to begin a run without misreading hall-effect sensor as a fake positive
double indexStickOff;

double indexLoop;//Random demonstration variables
double loopInterval = 5000000;

//Wave variables
int meanWave = 50;//Percentage extension
int wavePeriod = 3000;//Speed in seconds for a cicle
int waveSlope = 90;//Shift angle in degrees
int waveEntropy = 1;

int minWavePeriod = 2000;//in millis
int maxWavePeriod = 6000;//in millis
int minWaveSpeed = 3000;//in micros
int maxWaveSpeed = 400;//in micros

int regExtension;//In degrees
int regSpeed;
int regSlope;

int toGoSteps;

int waveExtension;
int waveSpeed;

//Cheesy variables
bool fg = 0;
double timeNext;
bool gf = 0;
bool sf = 0;

int ext;//Received extension
int spp;//Received Speed
int slp;//Received Slope

void setup()
{
  Serial.begin (2000000);
  Serial.println ("inicio");

  BT1.begin (9600);
  BT1.println ("BT running");
  
  setModes (); //Pins tab
  setInitials (); //Pins tab

  timeNow = micros ();
  calibrationRoutine ();//Calibration tab
  Serial.println ("In stepsLap");
  stepsLap ();//Calibration tab
  Serial.println ("stepsLap Finished");
  getWaves (1);//Waves tab
  testSequence ();
  Serial.println ("Test sequence finished");
}

void loop()
{
  timeNow = micros ();
  runAll ();
  if (Serial.available () > 0)
  {
    int mid = Serial.parseInt (); //Catch a number
    if (mid == 1500)
    {      
      st = 2000;
      extSpeed = st;
      intSpeed = extSpeed / 25;
      cBanner = 0;
      motorBanner1 = 0;
      motorBanner2 = 0;
      stepCounter = 0;
      fg = 0;
      sf = 0;      
      calibrationRoutine ();
      Serial.println ("CalibrationRoutine Done");
      stepsLap ();
      Serial.println ("stepsLap Done");
      getWaves (1);
      testSequence ();
      Serial.println ("Test sequence done");
    }
    else if (mid < 1000)
    {
      Serial.println ();
      Serial.println (mid);
      Serial.println ();

      //Golden combo generator. It needs 3 digit number via serial
      //works from 0 to 999

      spp = map (((mid / 100) % 10), 1, 9, 5000, 1800);//Hundreds
      ext = map (((mid / 10) % 10), 1, 9, 0, 100);//Tens
      slp = map ((mid % 10), 1, 9, 15, 180);//Ones
    }

    doThisThing();
  }
  if (BT1.available () != 0)
  {
    Serial.println ("Run bt command");
    int mid = BT1.parseInt (); //Catch a number
    if (mid == 1500)
    {      
      st = 10000;
      extSpeed = st;
      intSpeed = extSpeed / 25;
      cBanner = 0;
      motorBanner1 = 0;
      motorBanner2 = 0;
      stepCounter = 0;
      fg = 0;
      sf = 0;      
      calibrationRoutine ();
      Serial.println ("CalibrationRoutine Done");
      stepsLap ();
      Serial.println ("stepsLap Done");
      getWaves (1);
      testSequence ();
      Serial.println ("Test sequence done");
    }
    else if (mid < 1000 && mid > 0)
    {
      Serial.println ();
      Serial.println (mid);
      Serial.println ();

      //Golden combo generator. It needs 3 digit number via serial
      //works from 0 to 999

      spp = map (((mid / 100) % 10), 1, 9, 5000, 1800);//Hundreds
      ext = map (((mid / 10) % 10), 1, 9, 0, 100);//Tens
      slp = map ((mid % 10), 1, 9, 15, 180);//Ones
    }

    doThisThing();
  }

}
