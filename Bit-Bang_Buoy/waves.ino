void doSomething () //For random demonstration
{
  getWaves (2);//This tab
  waveRender ();
  waveDriver ();
}

void doOneThing ()
{
  waveRender ();
  waveDriver ();
}

void getWaves (byte y)
{
  switch (y)
  {
    case 1://constant
      meanWave = 3;//Percentage extension
      wavePeriod = 2500;//Speed
      waveSlope = 180;//Shift angle in degrees
      waveEntropy = 1;
      printCaseOne ();
      break;
    case 2://Random
      meanWave = random (0, 100);//In pecentage of extension
      wavePeriod = random (1, 10000);//In miliseconds
      waveSlope = random (40, 120);//In degrees from 0 to 360. from 10 to 120 for a natural feeling
      waveEntropy = random (1, 10);
      break;
    case 3:
      //get from wave watch 3 algorithm
      break;
    default:
      meanWave = meanWave;//Percentage extension
      wavePeriod = wavePeriod;//Speed
      waveSlope = waveSlope;//Shift angle
      waveEntropy = waveEntropy;
      break;
  }
}

void waveRender ()
{
  //
  waveExtension = map (meanWave, 0, 100, 0, 180);
  waveSpeed = map (wavePeriod, minWavePeriod, maxWavePeriod, maxWaveSpeed, minWaveSpeed);//We expect a linear relation between speed and steps in microsecodns
  //waveSlope = waveSlope;//no need changes since the input is in degrees

}

void waveDriver ()
{
  syncSpeed ();
  syncExtension ();  
  syncSlope ();
}


void syncExtension ()
{
  Serial.print ("waveExtension ");
  Serial.print (waveExtension);
  Serial.print (" regExtension");
  Serial.println (regExtension);
  if (waveExtension > regExtension)
  {
    fwExtension (waveExtension - regExtension);//Motors Tab. We pass the angle difference
  }
  if (waveExtension < regExtension)
  {
    rwExtension (regExtension - waveExtension);//Motors Tab
  }
  regExtension = waveExtension;
}

void syncSpeed ()
{
  Serial.print ("waveSpeed ");
  Serial.print (waveSpeed);
  Serial.print (" regSpeed ");
  Serial.println (regSpeed);
  st = waveSpeed;
  regSpeed = waveSpeed;
}

void syncSlope ()
{
  Serial.print ("waveSlope ");
  Serial.print (waveSlope);
  Serial.print (" regSlope");
  Serial.println (regSlope);
  if (waveSlope > regSlope)
  {
    fwSlope (waveSlope - regSlope);//Motors Tab. We pass the angle difference
  }
  if (waveSlope < regSlope)
  {
    rwSlope (regSlope - waveSlope);//Motors Tab
  }
  regSlope = waveSlope;
}

