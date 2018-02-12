void calibrationRoutine ()
{
  while (cBanner == 0)
  {
    readAll ();//Sensors tab
    //printSensors ();//Prints tab

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
    }

    if (dataS2 > detectS2 && motorBanner2 == 0)
    {
      calibrationRunMotor3 ();//Motors tab
      calibrationRunMotor4 ();
    }
    else if (dataS2 < detectS2 && motorBanner2 == 0)
    {
      motorBanner2 = 1;
      stop34 ();//Motors tab
      //speedCorrect ();//Motors tab. Not needed in newer versions
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
  timeLast = micros ();
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
    if (dataS1 < detectS1 || dataS2 < detectS2)
    {
      cBanner = 1;
    }
  }
  Serial.println (stepCounter);//StepCounter is increased in runAllTest. This count is needed to keep precision in shift angles
  //Status variables are setted
  regExtension = 180;//In degrees
  regSpeed = st; // WTF with me ->(timeNow - timeLast) / 1000;//in milliseconds
  regSlope = 0;//in degrees
}

