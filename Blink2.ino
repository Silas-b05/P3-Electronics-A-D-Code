void setup() {
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
}

void loop() { 
    
    unsigned long t = millis();

    digitalWrite(2, (t%1000) < 500 ? HIGH : LOW);
    digitalWrite(4, (t%2000) < 1000 ? HIGH : LOW);
}
