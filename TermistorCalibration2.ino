void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A2, INPUT);
}


void loop() {
    float SensorValue = analogRead(A0);
    float SensorValue2 = analogRead(A2);

    Serial.println("SensorValue: " + String(SensorValue) + ", SensorValue2: " + String(SensorValue2));

    #define DELAY 500
    delay(DELAY);
}