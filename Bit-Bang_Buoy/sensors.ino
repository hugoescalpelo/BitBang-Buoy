void readAll ()
{
  if (timeNow > indexRead)
  {
    dataS1 = analogRead (pinS1);
    dataS2 = analogRead (pinS2);
    indexRead = timeNow + readInterval;
  }
}

