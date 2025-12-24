#include <ESP8266WiFi.h>

const char* ssid = "Airtel_PoddarWIFI";
const char* password = "hello@123";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retry++;
    if (retry > 30) {   // 15 seconds timeout
      Serial.println("\nWiFi Failed!");
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
}
