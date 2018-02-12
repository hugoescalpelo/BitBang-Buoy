void calibrationRunMotor1 ()
{
  if (timeNow > indexOnExt)
  {
    digitalWrite (step1, HIGH);
    indexOnExt = timeNow + extSpeed;
  }
  if (timeNow > indexOffExt)
  {
    digitalWrite (step1, LOW);
    indexOffExt = indexOnExt + extSpeed;
  }
}

void calibrationRunMotor2 ()
{
  if (timeNow > indexOnInt)
  {
    digitalWrite (step2, HIGH);
    indexOnInt = timeNow + intSpeed;
  }
  if (timeNow > indexOffInt)
  {
    digitalWrite (step2, LOW);
    indexOffInt = indexOnInt + intSpeed;
  }
}

void stop12 ()
{
  digitalWrite (step1, LOW);
  digitalWrite (step2, LOW);
}

void speedCorrect ()
{
//  intSpeed = intSpeed / 2;
//  extSpeed = extSpeed / 2;
  intSpeed = intSpeed;
  extSpeed = extSpeed;
}

void calibrationRunMotor3 ()
{
  if (timeNow > indexOnExt2)
  {
    digitalWrite (step3, HIGH);
    indexOnExt2 = timeNow + extSpeed;
  }
  if (timeNow > indexOffExt2)
  {
    digitalWrite (step3, LOW);
    indexOffExt2 = indexOnExt2 + extSpeed;
  }
}

void calibrationRunMotor4 ()
{
  if (timeNow > indexOnInt2)
  {
    digitalWrite (step4, HIGH);
    indexOnInt2 = timeNow + intSpeed;
  }
  if (timeNow > indexOffInt2)
  {
    digitalWrite (step4, LOW);
    indexOffInt2 = indexOnInt2 + intSpeed;
  }
}

void stop34 ()
{
  digitalWrite (step3, LOW);
  digitalWrite (step4, LOW);
}

void runAll ()
{
  if (timeNow > indexOn)
  {
    digitalWrite (step1, HIGH);
    digitalWrite (step2, HIGH);
    digitalWrite (step3, HIGH);
    digitalWrite (step4, HIGH);
    indexOn = timeNow + st;
  }

  if (timeNow > indexOff)
  {
    digitalWrite (step1, LOW);
    digitalWrite (step2, LOW);
    digitalWrite (step3, LOW);
    digitalWrite (step4, LOW);
    indexOff = indexOn + st;
  }
}

void runAllTest ()
{
  if (timeNow > indexOn)
  {
    digitalWrite (step1, HIGH);
    digitalWrite (step2, HIGH);
    digitalWrite (step3, HIGH);
    digitalWrite (step4, HIGH);
    indexOn = timeNow + st;
    stepCounter++;
  }

  if (timeNow > indexOff)
  {
    digitalWrite (step1, LOW);
    digitalWrite (step2, LOW);
    digitalWrite (step3, LOW);
    digitalWrite (step4, LOW);
    indexOff = indexOn + st;
  }
}
