
void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
}

void loop()
{
int l = analogRead(2);

if (l > 300) {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
} else {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
}

}
