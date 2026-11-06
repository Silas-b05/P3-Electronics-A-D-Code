#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define colorR 255
#define colorG 255
#define colorB 255

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT);
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);  
    lcd.setRGB(colorR, colorG, colorB);
}

int previousState = HIGH;
unsigned long pulseCount = 0;
unsigned long lastMeasurement = 0;
int output = 0;
float integral = 0.0;
float previousError = 0.0;
float previousTemp = 0.0;
#define Kp 50.0
#define Ki 15.0
#define Kd 0.5

void loop() {

    float SensorValueTemp = analogRead(A0);
    #define T0 298.15
    #define B 4561.308112063196
    float Temperature_x = 1/(log(1023/SensorValueTemp - 1)/B + 1/T0) - 273.15;

    // Low-pass
    #define alpha 0.5
    float Temperature = alpha*Temperature_x+(1-alpha)*previousTemp;
    previousTemp = Temperature;

    int sensor_value_potentiometer = analogRead(A2);

    #define upper_limit 30.0
    #define lower_limit 20.0
    float GoalTemp = map(sensor_value_potentiometer, 0, 1023, lower_limit, upper_limit);

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

        Serial.println(Temperature);
        lcd.setCursor(0, 0);
        lcd.print("RPM: " + String(rpm));
      
        lcd.setCursor(0, 0);
        lcd.print("RPM: " + String(rpm) + "    ");

        lcd.setCursor(0, 1);
        lcd.print("G:" + String(GoalTemp) + ", T:" + String(Temperature));


        pulseCount = 0;
        lastMeasurement = currentTime;

        float error = Temperature - GoalTemp;

        float derivative = (error - previousError) / deltaTime;

        float u = Kp * error + Ki * integral + Kd * derivative;

        if ((u < 255 && u > 0) || (u >= 255 && error < 0) || (u <= 0 && error > 0)) {
            ntegral += error * deltaTime;
        }

        u = Kp * error + Ki * integral + Kd * derivative;

        previousError = error;

        int dutyCycle = constrain((int)u, 0, 255);
        analogWrite(10, dutyCycle);

    }
}