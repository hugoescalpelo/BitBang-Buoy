void setModes ()
{
  pinMode (dir1, OUTPUT);
  pinMode (step1, OUTPUT);
  pinMode (dir2, OUTPUT);
  pinMode (step2, OUTPUT);
  pinMode (dir3, OUTPUT);
  pinMode (step3, OUTPUT);
  pinMode (dir4, OUTPUT);
  pinMode (step4, OUTPUT);
}

void setInitials ()
{
  digitalWrite (dir1, HIGH);
  digitalWrite (step1, LOW);
  digitalWrite (dir2, HIGH);
  digitalWrite (step2, LOW);
  digitalWrite (dir3, HIGH);
  digitalWrite (step3, LOW);
  digitalWrite (dir4, HIGH);
  digitalWrite (step4, LOW);
}
