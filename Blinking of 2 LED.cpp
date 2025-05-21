// Blinking of two LEDs using 2 Push Button and data send to Thingspeak

#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "YOUR_WIFI_SSID";         // Replace with your WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your WiFi password
const unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER; // Replace with your ThingSpeak channel number
const char* myWriteAPIKey = "YOUR_WRITE_API_KEY";          // Replace with your ThingSpeak Write API key

WiFiClient client;

const int button1 = 13; // GPIO pin for button 1
const int button2 = 14; // GPIO pin for button 2
const int led1 = 25;    // GPIO pin for LED 1
const int led2 = 26;    // GPIO pin for LED 2

bool led1State = false;
bool led2State = false;

void setup() {
    Serial.begin(115200);
    
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
}

void loop() {
    static bool lastLed1State = led1State;
    static bool lastLed2State = led2State;

    if (digitalRead(button1) == LOW) {
        delay(200); // Debounce delay
        led1State = !led1State;
        digitalWrite(led1, led1State);
    }

    if (digitalRead(button2) == LOW) {
        delay(200); // Debounce delay
        led2State = !led2State;
        digitalWrite(led2, led2State);
    }

    // Send to ThingSpeak only if there's a change
    if (led1State != lastLed1State || led2State != lastLed2State) {
        Serial.println("Updating ThingSpeak...");

        ThingSpeak.setField(1, led1State ? 1 : 0);
        ThingSpeak.setField(2, led2State ? 1 : 0);
        
        int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if (x == 200) {
            Serial.println("Update successful.");
        } else {
            Serial.print("Error code: ");
            Serial.println(x);
        }

        lastLed1State = led1State;
        lastLed2State = led2State;
    }

    delay(100); // Reduce CPU usage
}
