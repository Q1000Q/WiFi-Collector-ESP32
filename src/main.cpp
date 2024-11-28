#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>

const char* ESP_SSID = "WiFi-Collector";
const char* ESP_PASSWORD = "Admin";

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.softAP(ESP_SSID, ESP_PASSWORD);

  pinMode(2, OUTPUT);

  Serial.println("Setup done");
}

void loop() {

  // WiFi.scanNetworks will return the number of networks found
  digitalWrite(2, HIGH);
  int n = WiFi.scanNetworks();
  digitalWrite(2, LOW);

  // Check if networks were found and list them
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}