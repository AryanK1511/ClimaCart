#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define TMP36_PIN 34

const char *ssid_Router = "Hasan";     
const char *password_Router = "Aarih2022!"; 
const char* server_url = "http://192.168.2.54:3000"; 

void setup() {
  Serial.begin(115200);
  delay(2000);

  WiFi.begin(ssid_Router, password_Router);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println(WiFi.localIP());
}

void loop() {
  int analogValue = analogRead(TMP36_PIN);
  float voltage = (analogValue / 1023.0);
  float temperatureC = (voltage - .5) * 100;

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" °C");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    StaticJsonDocument<200> doc;
    doc["value"] = temperatureC;

    char jsonString[256];
    serializeJson(doc, jsonString);

    http.begin(server_url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
      Serial.printf("POST Request successful. Response code: %d\n", httpResponseCode);
    } else {
      Serial.printf("Error in POST request. Response code: %d\n", httpResponseCode);
    }

    http.end();
  }

  delay(2000);
}
