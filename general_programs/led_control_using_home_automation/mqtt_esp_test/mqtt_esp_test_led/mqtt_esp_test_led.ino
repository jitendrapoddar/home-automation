#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Airtel_PoddarWIFI";
const char* password = "hello@123";

const char* mqtt_server = "192.168.1.12";  // Raspberry Pi IP

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message arrived: ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(LED_BUILTIN, LOW);   // LED ON
    client.publish("home/esp12/led/state", "ON");
  } 
  else if (message == "OFF") {
    digitalWrite(LED_BUILTIN, HIGH);  // LED OFF
    client.publish("home/esp12/led/state", "OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP12_Client")) {
      Serial.println("connected");
      client.subscribe("home/esp12/led/set");
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
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
