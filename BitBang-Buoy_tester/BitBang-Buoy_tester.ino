int d1;
int d2;

void setup() 
{
  Serial.begin (2000000);
  Serial.println ("inicio!");
  
}

void loop() 
{
  d1 = analogRead (A0);
  d2 = analogRead (A1);
  Serial.print (d1);
  Serial.print (" ");
  Serial.println (d2);
}
