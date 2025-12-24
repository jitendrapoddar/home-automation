void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // Set built-in LED as output
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // LED ON
  delay(1000);                      // 1 second delay
  digitalWrite(LED_BUILTIN, HIGH);  // LED OFF
  delay(1000);                      // 1 second delay
}
