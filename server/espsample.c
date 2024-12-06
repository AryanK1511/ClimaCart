#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* websocket_server = "https://36b4-142-181-192-78.ngrok-free.app"; // Your server's IP
const int websocket_port = 8080;

WebSocketsClient webSocket;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Connect to WebSocket server
    webSocket.begin(websocket_server, websocket_port, "/");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
}

void loop() {
    webSocket.loop();
    
    // Send sensor data every 5 seconds
    static unsigned long lastSendTime = 0;
    if (millis() - lastSendTime > 5000) {
        sendSensorData();
        lastSendTime = millis();
    }
}

void sendSensorData() {
    StaticJsonDocument<200> doc;
    doc["temperature"] = 25.6; // Replace with actual sensor reading
    doc["humidity"] = 60;      // Replace with actual sensor reading
    
    String jsonString;
    serializeJson(doc, jsonString);
    webSocket.sendTXT(jsonString);
}
