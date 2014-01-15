void setup()
{  
  pinMode(LED_BUILTIN, OUTPUT);
  delay(5000);
  on(0.1);
  off(0.1);
  on(0.1);
  off(0.1);
  on(0.2);
  off(0.2);
  on(0.5);
  off(0.5);
  on(1);
  off(1);
  Serial.begin(9600);
  
}

void on(float sec) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay ((int)(sec*1000));
  Serial.print("Temperature: ");
}

void off(float sec) {
  digitalWrite(LED_BUILTIN, LOW);
  delay((int)(sec*1000));
}

void loop()
{
int i, max = 100;
float d = 0.2;
on(1);
off(0.2);
Serial.println(1);
}
