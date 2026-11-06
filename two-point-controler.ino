#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(10, OUTPUT);
    lcd.begin(16, 2);
    digitalWrite(10, LOW);
    Serial.begin(9600);

}

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

    #define upper_limit 30.0
    #define lower_limit 20.0
    THRESHOLD = map(sensor_value_potentiometer, 0, 1023, lower_limit, upper_limit);
    float lower_THRESHOLD = THRESHOLD - 2.0;

    // converting the analog reading to temperature in Celsius
    float Temperature = 1/(log(1023/SensorValue - 1)/B + 1/T0) - 273.15;

    if (Temperature > THRESHOLD || Temperature < lower_THRESHOLD) {
        colorR = 255;
        colorG = 0;
        colorB = 0;
        lcd.setRGB(colorR, colorG, colorB);
    }
    else {
        colorR = 255;
        colorG = 255;
        colorB = 255;
        lcd.setRGB(colorR, colorG, colorB);
    }

    if (Temperature > THRESHOLD) {
        digitalWrite(10, HIGH);
    }
    else if (Temperature < lower_THRESHOLD) {
        digitalWrite(10, LOW);
    }

    lcd.setCursor(0, 0);
    lcd.print("Limit: " + String(THRESHOLD) + " C");

    lcd.setCursor(0, 1);

    lcd.print("Temp : " + String(Temperature) + " C");

    Serial.println(Temperature);

    #define DELAY 200
    delay(DELAY);
}