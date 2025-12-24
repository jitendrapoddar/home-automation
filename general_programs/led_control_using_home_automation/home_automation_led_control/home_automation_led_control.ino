#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Airtel_PoddarWIFI";
const char* password = "hello@123";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "ESP12 is running");
}

void handleLedOn() {
  digitalWrite(LED_BUILTIN, LOW);   // LED ON (active LOW)
  server.send(200, "text/plain", "LED ON");
}

void handleLedOff() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED OFF
  server.send(200, "text/plain", "LED OFF");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("ESP IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
