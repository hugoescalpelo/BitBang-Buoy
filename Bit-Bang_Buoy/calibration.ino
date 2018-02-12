void calibrationRoutine ()
{
  while (cBanner == 0)
  {
    readAll ();
    //printSensors ();

    timeNow = micros ();

    if (dataS1 > detectS1 && motorBanner1 == 0)
    {
      calibrationRunMotor1 ();
      calibrationRunMotor2 ();
    }
    else if (dataS1 < detectS1 && motorBanner1 == 0)
    {
      motorBanner1 = 1;
      stop12 ();
      speedCorrect ();
    }

    if (dataS2 > detectS2 && motorBanner2 == 0)
    {
      calibrationRunMotor3 ();
      calibrationRunMotor4 ();
    }
    else if (dataS2 < detectS2 && motorBanner2 == 0)
    {
      motorBanner2 = 1;
      stop34 ();
      speedCorrect ();
    }

    if (motorBanner1 == 1 && motorBanner2 == 1)
    {
      cBanner = 1;
    }
  }
}

void twoLevelStepCounter ()
{
  //st = st/2;
  cBanner = 0;
  timeNow = micros ();
  indexStickOff = timeNow + stickOffTime;

  while (cBanner == 0)
  {
    timeNow = micros ();
    readAll ();
    runAllTest ();
    if (timeNow > indexStickOff)
    {
      cBanner = 1;
    }
  }
  cBanner = 0;
  while (cBanner == 0)
  {
    timeNow = micros ();
    readAll ();
    runAllTest ();
    if (dataS1 < detectS1 || dataS2 < detectS2)
    {
      cBanner = 1;
    }
  }
  Serial.println (stepCounter);

  //st = st*2;
  stepCounter = 0;

  cBanner = 0;
  timeNow = micros ();
  indexStickOff = timeNow + stickOffTime;

  while (cBanner == 0)
  {
    timeNow = micros ();
    //readAll ();
    runAllTest ();
    if (timeNow > indexStickOff)
    {
      cBanner = 1;
    }
  }
  cBanner = 0;
  while (cBanner == 0)
  {
    timeNow = micros ();
    readAll ();
    runAllTest ();
    if (dataS1 < detectS1 || dataS2 < detectS2)
    {
      cBanner = 1;
    }
  }
  Serial.println (stepCounter);
}

