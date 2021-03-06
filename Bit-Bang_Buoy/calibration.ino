void calibrationRoutine ()
{
  while (cBanner == 0)
  {
    readAll ();//Sensors tab
    printSensors ();//Prints tab
    //BTPrintSensors ();

    timeNow = micros ();

    if (dataS1 > detectS1 && motorBanner1 == 0)
    {
      calibrationRunMotor1 ();//Motors tab
      calibrationRunMotor2 ();
      
    }
    else if (dataS1 < detectS1 && motorBanner1 == 0)
    {
      motorBanner1 = 1;
      stop12 ();//Motors tab
      //speedCorrect ();//Motors tab. Not needed in newer versions
      Serial.println ("Motor1 stop");
      BT1.println("motor1 stop");
    }

    if (dataS2 < detectS2 && motorBanner2 == 0)
    {
      calibrationRunMotor3 ();//Motors tab
      calibrationRunMotor4 ();
    }
    else if (dataS2 > detectS2 && motorBanner2 == 0)
    {
      motorBanner2 = 1;
      stop34 ();//Motors tab
      //speedCorrect ();//Motors tab. Not needed in newer versions
      Serial.println ("Motor2 stop");
      BT1.println("motor2 stop");
    }

    if (motorBanner1 == 1 && motorBanner2 == 1)
    {
      cBanner = 1;
    }
  }
}

void stepsLap ()
{
  //st = st/2;
  cBanner = 0;
  //timeLast = micros ();
  timeNow = micros ();
  indexStickOff = timeNow + stickOffTime;//This prevents a fake positive on sensors read at the begining of a new run

  while (cBanner == 0)
  {
    timeNow = micros ();
    readAll ();//Sensors tab
    runAllTest ();//Motors tab
    if (timeNow > indexStickOff)
    {
      cBanner = 1;
    }
  }
  cBanner = 0;
  while (cBanner == 0)
  {
    timeNow = micros ();
    readAll ();//Sensors tab
    runAllTest ();//Motors tab
    if (dataS1 < detectS1 || dataS2 > detectS2)
    {
      cBanner = 1;
    }
  }
  Serial.print ("Steps per lap ");
  Serial.println (stepCounter);//StepCounter is increased in runAllTest. This count is needed to keep precision in shift angles
  //Status variables are setted
  regExtension = 0;//In degrees
  regSpeed = st; // WTF with me ->(timeNow - timeLast) / 1000;//in milliseconds
  regSlope = 0;//in degrees
}

void testSequence ()
{
  bool od = 0;
  while (od == 0)
  {
    timeNow = micros ();

    runAll ();
    if (fg == 0)
    {
      Serial.println ("do one thing");
      wavePeriod = 4900;
      doOneThing ();
      fg = 1;
      timeNext = micros () + 5000000;
    }

    if (timeNow > timeNext && gf == 0)
    {
      Serial.println ("Change meanwave");
      meanWave = 50;
      doOneThing ();
      gf = 1;
      timeNext = micros () + 5000000;
    }

    if (timeNow > timeNext && sf == 0)
    {
      Serial.println ("Change waveSlope");
      waveSlope = 45;
      doOneThing ();
      sf = 1;
      od = 1;
    }
  }
}

