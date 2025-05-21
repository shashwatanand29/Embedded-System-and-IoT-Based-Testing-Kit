//Object detection using IR Sensor & buzzer and display it on Thingspeak 

#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "WIFI SSID";      
const char* password = "PASSWORD"; 
const char* thingSpeakApiKey = "API KEY"; 

WiFiClient client;

const int irSensorPin = 14;  // Define the GPIO pin connected to the IR sensor
const int buzzerPin = 26;    // Define the GPIO pin connected to the buzzer

unsigned long myChannelNumber =  2827968; // Replace with your ThingSpeak Channel Number

void setup() {
  Serial.begin(115200);  // Start the serial communication
  pinMode(irSensorPin, INPUT);  // Set IR sensor pin as input
  pinMode(buzzerPin, OUTPUT);   // Set buzzer pin as output

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);  // Read the sensor value

  Serial.print("IR Sensor Status: ");
  Serial.println(sensorValue == LOW ? "Object Detected" : "No Object Detected");

  if (sensorValue == LOW) {
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    ThingSpeak.writeField(myChannelNumber, 1, 1, thingSpeakApiKey); // Send data to ThingSpeak
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
    ThingSpeak.writeField(myChannelNumber, 1, 0, thingSpeakApiKey); // Send data to ThingSpeak
  }

  delay(200);  // Reduced delay to 5 seconds
}
