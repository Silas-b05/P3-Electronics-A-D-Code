void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A2, INPUT);
}

unsigned long B2 = 4200;

void loop() {
    float SensorValue = analogRead(A0);
    float SensorValue2 = analogRead(A2);
    #define T0 298.15
    #define B 4275

    // converting the analog reading to temperature in Celsius
    float Temperature = 1/(log(1023/SensorValue - 1)/B + 1/T0) - 273.15;
    float Temperature2 = 1/(log(1023/SensorValue2 - 1)/B2 + 1/T0) - 273.15;
    float error = abs(Temperature - Temperature2);
    Serial.println("GroveTemperature: " + String(Temperature) + ", ThermistorTemperature: " + String(Temperature2) + ", Error: " + String(error) + ", B2: " + String(B2));
    B2++;
    #define DELAY 200
    delay(DELAY);
}
