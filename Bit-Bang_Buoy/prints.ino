void printSensors ()
{
  Serial.print (dataS1);
  Serial.print (" ");
  Serial.println (dataS2);
}

void printCaseOne ()
{
  Serial.print ("meanWave ");
  Serial.print (meanWave);
  Serial.print (" wavePeriod ");
  Serial.print (wavePeriod);
  Serial.print (" waveSlope ");
  Serial.print (waveSlope);
  Serial.print (" waveEntropy ");
  Serial.println (waveEntropy);
}

