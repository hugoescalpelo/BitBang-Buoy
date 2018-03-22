void readAll ()
{
  if (timeNow > indexRead)
  {
    dataS1 = analogRead (A1);
    dataS2 = analogRead (A0);
    indexRead = timeNow + readInterval;
  }
}

