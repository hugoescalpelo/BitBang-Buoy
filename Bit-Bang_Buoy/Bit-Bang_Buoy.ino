/*
 * Ivan Abreu Studio.
 * 
 * 12/2/2018. México City.
 * 
 * This code drives a mechanism that simulate sea waves, it has 4
 * stepper motors with TB6600 micro stepper driver.
 * 
 * The code was rewriten to work with no libraries because they
 * fail at guarantee synchronicity and precise angle control.
 * 
 * This code use bitbang control, which means it works with HIGH-LOW
 * toggle on every driver pin. Time is controled independently with
 * micros function.
 * 
 * This version its kind of half way. Next topics are intendeed to be developed:
 * 
 * -Golden combinations
 * -Manual calibration command
 * -Always calibrating routine
 * -Real time data extract from WW3 algorithm
 * 
 * Team:
 * 
 * Iván Abreu Ochoa
 * Malitzin Cortez
 * Beto Olguin
 * Hugo Vargas
 */

//Driver pins
int dir1 = 5;
int step1 = 6;
int dir2 = 7;
int step2 = 8;
int dir3 = 9;
int step3 = 10;
int dir4 = 11;
int step4 = 12;

int st = 2000;

//time variables
double timeNow;
double timeLast;
double indexOn;
double indexOff;

//Sensor variables
int pinS1 = 5;
int dataS1 = 0;
int detectS1 = 421;

int pinS2 = 4;
int dataS2 = 0;
int detectS2 = 424;

//Calibration variables
  byte cBanner = 0;

  int extSpeed = st;
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

  int ext;
  int spp;
  int slp;

void setup() 
{
  Serial.begin (2000000);
  Serial.println ("inicio");

  setModes (); //Pins tab
  setInitials (); //Pins tab

  timeNow = micros ();
  calibrationRoutine ();//Calibration tab
  Serial.println ("In stepsLap");
  stepsLap ();//Calibration tab
  Serial.println ("out of stepsLap");
  getWaves (1);//Waves tab
  testSequence ();
}

void loop() 
{
  timeNow = micros ();
  runAll ();
  if (Serial.available () > 0)
  {
    ext = Serial.parseInt ();
    spp = Serial.parseInt ();
    slp = Serial.parseInt ();

    Serial.println (":)");

    doThisThing();
  }
  
}
