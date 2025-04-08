#include <Wire.h>               // For I2C communication
#include <LiquidCrystal_I2C.h>  // For I2C 16x2 LCD
#include <Adafruit_TCS34725.h>  // For TSC34725 Sensor

// Digital Pins for LEDs, Buzzer, and TCS34725
#define BUZZER 2
#define GREEN_LED 3
#define RED_LED 4
#define CASE_LED 8

// Digital Pin for TCRT5000 sensor
#define IR_SENSOR 6

// Digital Pin for LJ12A3-4-Z/BX sensor
#define INDUCTIVE_SENSOR 10

// Digital Pin for LJC18A3-B-Z/BY sensor
#define CAPACITIVE_SENSOR 12

// Analog Pins (shared) for I2C LCD, and TCS34725 sensor
    // SDA = A4
    // SCL = A5

LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_TCS34725 tcs;

// Global variables
String lastMessage1 = "";
String lastMessage2 = "";
static unsigned long lastActivityTime = 0;
bool isDark = false;


void errorHandler(const String& sensor) {
    Serial.println("ERROR: " + sensor + " sensor may be DISCONNECTED! CHECK WIRING!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(sensor + " ERROR");
    lcd.setCursor(0, 1);
    lcd.print("CHECK WIRING!");
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    delay(100);
    while (1);
}

void displayMessage(String line1, String line2) {
    if (line1 != lastMessage1 || line2 != lastMessage2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);

        lastMessage1 = line1;
        lastMessage2 = line2;
    }
}

void checkIfDark() {
    const uint16_t darknessThreshold = 50;

    uint16_t clear, red, green, blue;
    tcs.getRawData(&red, &green, &blue, &clear);

    Serial.print("Clear: ");
    Serial.println(clear);

    if (clear < darknessThreshold) { isDark = true; }
    else isDark = false;
}

void timeoutHandler() {
    const unsigned long timeout = 60000; // 60 seconds

    if (millis() - lastActivityTime >= timeout) {
        lcd.noBacklight();
        digitalWrite(CASE_LED, LOW);

        checkIfDark();
    }
    else {
        if(isDark) { digitalWrite(CASE_LED, HIGH); }
        else digitalWrite(CASE_LED, LOW);
    }
}

void setup() {
    pinMode(BUZZER, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(CASE_LED, OUTPUT);
    pinMode(IR_SENSOR, INPUT);
    pinMode(INDUCTIVE_SENSOR, INPUT);
    pinMode(CAPACITIVE_SENSOR, INPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.clear();

    if (!tcs.begin()) {
        errorHandler("TCS34725");
    }
    
    tcs.setGain(TCS34725_GAIN_1X);
    tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_240MS);

    displayMessage("-- WiseWaste --", "Initializing...");
    
    digitalWrite(CASE_LED, HIGH);
    for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER, HIGH);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, HIGH);
        tcs.setInterrupt(false);
        delay(250);
        digitalWrite(BUZZER, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, LOW);
        tcs.setInterrupt(true);
        delay(250);
    }
    digitalWrite(CASE_LED, LOW);
    delay(1000);
    checkIfDark();
}

void loop() {
    displayMessage("-- WiseWaste --", "Scan Object Here");

    // Check if TCRT5000 IR Sensor detected an non-black object
    bool objectDetected = digitalRead(IR_SENSOR) == LOW;

    if (objectDetected) {
        delay(300);
    }

    // Independently Read Capacitive and Inductive Sensor
    bool isDielectric = digitalRead(CAPACITIVE_SENSOR) == HIGH;
    bool isMetal = digitalRead(INDUCTIVE_SENSOR) == LOW;

    // Object Classification
    if (isDielectric && !isMetal) { // Biodegradable Detected
        lcd.backlight();
        tcs.setInterrupt(false);

        digitalWrite(GREEN_LED, HIGH);
        displayMessage("Biodegradable", "MaterialDetected");

        for (int i = 0; i < 3; i++) {
            digitalWrite(BUZZER, HIGH);
            delay(50);
            digitalWrite(BUZZER, LOW);
            delay(50);
        }
        delay(200);
    } 

    if (isMetal) { // Non-Biodegradable
        lcd.backlight();
        tcs.setInterrupt(false);

        digitalWrite(RED_LED, HIGH);
        displayMessage("NonBiodegradable", "Metal Detected");

        digitalWrite(BUZZER, HIGH);
        delay(500);
        digitalWrite(BUZZER, LOW);
    }

    if (objectDetected && !isDielectric && !isMetal) { // Plastic Detected
        lcd.backlight();
        tcs.setInterrupt(false);

        digitalWrite(RED_LED, HIGH);
        displayMessage("NonBiodegradable", "Plastic Detected");

        digitalWrite(BUZZER, HIGH);
        delay(500);
        digitalWrite(BUZZER, LOW);
    }

    if (objectDetected || isDielectric || isMetal) {
        
        delay(1000);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, LOW);
        tcs.setInterrupt(true);

        lastActivityTime = millis();
    }

    timeoutHandler();

    delay(100);
}


// Authored by: Jay Garcia
// Contact @ github: K1taru