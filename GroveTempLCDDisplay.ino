#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
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

    // set the cursor to column 0, line 1
    lcd.setCursor(0, 1);
    // print the temperature to the LCD
    lcd.print("Temp: " + String(Temperature) + " C");

    #define DELAY 1000
    delay(DELAY);
}
