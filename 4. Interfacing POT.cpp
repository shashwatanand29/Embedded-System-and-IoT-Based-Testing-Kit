//Interfacing Potentiometer for changing voltage and display data on Thingspeak

#include <WiFi.h>
#include "ThingSpeak.h"

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";          // Replace with your WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your WiFi Password

// ThingSpeak credentials
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;      // Replace with your ThingSpeak channel number
const char* myWriteAPIKey = "YOUR_WRITE_API_KEY";         // Replace with your ThingSpeak Write API Key

WiFiClient client;

// Potentiometer pin
#define POTENTIOMETER_PIN 33  // Must be an ADC-capable pin

void setup() {
    Serial.begin(115200);
    
    // Start WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
}

void loop() {
    // Read analog value and convert to voltage
    int potValue = analogRead(POTENTIOMETER_PIN);
    float voltage = (potValue / 4095.0) * 3.3;

    // Print to serial monitor
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Voltage: ");
    Serial.println(voltage, 2);

    // Send to ThingSpeak
    ThingSpeak.setField(1, potValue);       // Field 1: Raw potentiometer value
    ThingSpeak.setField(2, voltage);        // Field 2: Converted voltage

    int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (status == 200) {
        Serial.println("Data sent to ThingSpeak successfully.");
    } else {
        Serial.print("ThingSpeak update error, code: ");
        Serial.println(status);
    }

    delay(15000); // ThingSpeak accepts updates every 15 seconds
}
