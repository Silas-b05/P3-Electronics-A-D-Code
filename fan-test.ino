void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A1);
  digitalWrite(10, HIGH);
  delay(2000);
  digitalWrite(10, LOW);
  delay(2000);
  }