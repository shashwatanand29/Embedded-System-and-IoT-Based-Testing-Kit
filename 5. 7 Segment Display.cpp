//Counting on 7 Segment Display and send data on Thingspeak 

#include <WiFi.h>
#include "ThingSpeak.h"

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";          // Replace with your WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your WiFi password

// ThingSpeak configuration
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;      // Replace with your channel number
const char* myWriteAPIKey = "YOUR_WRITE_API_KEY";         // Replace with your Write API Key

WiFiClient client;

// Pin definitions
#define BUTTON_PIN 13  // Push button for Play/Pause
#define DP_PIN 15      // Decimal Point Pin

const int segmentPins[7] = {12, 14, 27, 26, 25, 33, 32};

const byte numbers[10][7] = {
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 1, 0, 0}  // 9
};

volatile bool isPaused = false;
int currentNumber = 0;
unsigned long lastUpdateTime = 0;

void IRAM_ATTR handleButtonPress() {
    isPaused = !isPaused;
}

void displayNumber(int num) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], numbers[num][i] ? HIGH : LOW);
    }
}

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }

    pinMode(DP_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON_PIN, handleButtonPress, FALLING);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
}

void loop() {
    if (!isPaused) {
        displayNumber(currentNumber);

        if (currentNumber == 9) {
            // Blink decimal point
            digitalWrite(DP_PIN, LOW);
            delay(500);
            digitalWrite(DP_PIN, HIGH);
            delay(500);
        }

        // Send current number to ThingSpeak every time it updates
        ThingSpeak.setField(1, currentNumber);
        int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

        if (status == 200) {
            Serial.print("Sent to ThingSpeak: ");
            Serial.println(currentNumber);
        } else {
            Serial.print("ThingSpeak error: ");
            Serial.println(status);
        }

        currentNumber = (currentNumber + 1) % 10;
        delay(1000); // Update every 1 second
    }
}
