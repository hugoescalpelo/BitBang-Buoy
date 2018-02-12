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

//void twoLevelStepCounter ()
//{
//  cBanner = 0;
//  while (cBanner == 0)
//  {
//    timeNow = micros ();
//    readAll (
//    runAll ();
//  }
//  timeNow = micros ();
//  runAll ();
//}

