#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    pinMode(A0, INPUT);
    pinMode(A2, INPUT);

}

void loop() {

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    int colorR = 0;
    int colorG = 0;
    int colorB = 0;


    float SensorValue = analogRead(A0);
    #define T0 298.15
    #define B 4275

    float THRESHOLD;

    int sensor_value_potentiometer = analogRead(A2);

    #define upper_limit 30.0
    #define lower_limit 20.0
    THRESHOLD = map(sensor_value_potentiometer, 0, 1023, lower_limit, upper_limit);

    // converting the analog reading to temperature in Celsius
    float Temperature = 1/(log(1023/SensorValue - 1)/B + 1/T0) - 273.15;

    if (Temperature > THRESHOLD) {
        colorR = 0;
        colorG = 255;
        colorB = 0;
        lcd.setRGB(colorR, colorG, colorB);
    }
    else {
        colorR = 255;
        colorG = 0;
        colorB = 0;
        lcd.setRGB(colorR, colorG, colorB);
    }

    lcd.setCursor(0, 0);
    lcd.print("Threshold: " + String(THRESHOLD) + " C");

    // set the cursor to column 0, line 1
    lcd.setCursor(0, 1);
    // print the temperature to the LCD
    lcd.print("Temp: " + String(Temperature) + " C");

    #define DELAY 1000
    delay(DELAY);
}
