#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Airtel_PoddarWIFI";
const char* password = "hello@123";
const char* mqtt_server = "192.168.1.12";  // Raspberry Pi IP

WiFiClient espClient;
PubSubClient client(espClient);

const char* stateTopic = "home/esp12/led/state";
const char* commandTopic = "home/esp12/led/set";

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) message += (char)payload[i];

  if (message == "ON") {
    digitalWrite(LED_BUILTIN, LOW);
    client.publish(stateTopic, "ON");
  } 
  else if (message == "OFF") {
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish(stateTopic, "OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP12_Client_01")) {
      Serial.println("connected");
      client.subscribe(commandTopic);
      // Publish current state after reconnect
      if (digitalRead(LED_BUILTIN) == LOW) client.publish(stateTopic, "ON");
      else client.publish(stateTopic, "OFF");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
