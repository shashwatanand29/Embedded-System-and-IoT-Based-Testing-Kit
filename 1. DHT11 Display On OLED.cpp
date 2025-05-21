//Temperature & Humidity test using DHT11 display on OLED and send data to Thingspeak

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// WiFi Credentials
const char* ssid = "WIFI SSID";
const char* password = "PASSWORD";

// ThingSpeak Settings
String apiKey = "API KEY";
const char* server = "http://api.thingspeak.com/update";

// DHT Settings
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Custom I2C Pins (SDA = GPIO32, SCL = GPIO33)
TwoWire customWire(0);

// OLED Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &customWire, OLED_RESET);

// Function to display on OLED and Serial
void displayData(float temperature, float humidity) {
  // Serial Output
  Serial.println("========== Sensor Data ==========");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println("=================================\n");

  // OLED Output
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Temp & Hum Monitor");
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print("T: ");
  display.print(temperature);
  display.println(" C");
  display.setCursor(0, 40);
  display.print("H: ");
  display.print(humidity);
  display.println(" %");
  display.display();
}

void setup() {
  Serial.begin(115200);
  customWire.begin(32, 33);  // SDA = GPIO32, SCL = GPIO33

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Halt if OLED not found
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  display.println("WiFi Connected!");
  display.display();
  delay(1000);

  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Sensor Error!");
    display.display();
    delay(1500);
    return;
  }

  // Display on Serial and OLED
  displayData(temperature, humidity);

  // Send to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temperature) + "&field2=" + String(humidity);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak.");
    } else {
      Serial.println("ThingSpeak update failed.");
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected.");
  }

  delay(1500); // Update every 5 seconds
}
