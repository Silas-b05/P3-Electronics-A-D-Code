#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT);
    pinMode(10, OUTPUT);
    analogWrite(10, 0);
    lcd.begin(16, 2);
    Serial.begin(9600);

}

int previousState = HIGH;
unsigned long pulseCount = 0;
unsigned long lastMeasurement = 0;
int output = 0;

void loop() {



    // set up the LCD's number of columns and rows:
    
    
    int colorR = 0;
    int colorG = 0;
    int colorB = 0;


    float SensorValue = analogRead(A0);
    #define T0 298.15
    #define B 4561.308112063196

    float THRESHOLD;

    int sensor_value_potentiometer = analogRead(A2);

    // converting the analog reading to temperature in Celsius
    float Temperature = 1/(log(1023/SensorValue - 1)/B + 1/T0) - 273.15;

    colorR = 255;
    colorG = 255;
    colorB = 255;
    lcd.setRGB(colorR, colorG, colorB);


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

        Serial.println(String(rpm));
      
        pulseCount = 0;
        lastMeasurement = currentTime;
            // Update LCD
        lcd.setCursor(0, 0);
        lcd.print("RPM: " + String(rpm) + "    ");

        lcd.setCursor(0, 1);
        lcd.print("Temp: " + String(Temperature) + " C  ");

        // Serial output
        Serial.print("RPM: ");
        Serial.print(rpm);
        Serial.print(", Temp: ");
        Serial.println(Temperature);

        pulseCount = 0;
        lastMeasurement = currentTime;
    }
}