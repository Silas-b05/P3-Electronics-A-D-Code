void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
}

void loop() {
    float SensorValue = analogRead(A0);
    #define T0 298.15
    #define B 4275

    // converting the analog reading to temperature in Celsius
    float Temperature = 1/(log(1023/SensorValue - 1)/B + 1/T0) - 273.15;
    Serial.println(Temperature);
    #define DELAY 1000
    delay(DELAY);
}
