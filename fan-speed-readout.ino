void setup() {
    Serial.begin(9600);

    pinMode(10, OUTPUT);
    pinMode(A1, INPUT_PULLUP);
    digitalWrite(10, LOW);

}

int previousState = HIGH;
unsigned long pulseCount = 0;
unsigned long lastMeasurement = 0;
int output = 0;

void loop() {

    int sensorValue = analogRead(A1);
    int currentState = (sensorValue > 512) ? HIGH : LOW;

    if (previousState == HIGH && currentState == LOW) {
        pulseCount++;
    }

    previousState = currentState;

    unsigned long currentTime = millis();

    

    if (currentTime - lastMeasurement >= 1000) {
        float deltaTime = (currentTime - lastMeasurement) / 1000.0;

        float rpm = pulseCount * 60.0 / (2.0 * deltaTime);

        Serial.println(String(rpm) + "," + String(output));
        if (output < 255) {
            analogWrite(10, ++output);
        } else {
            analogWrite(10, output);
        }
      
        pulseCount = 0;
        lastMeasurement = currentTime;
    }
}