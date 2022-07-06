#include "mqttapp.h"
#include "wifiapp.h"

WiFiClient ubidots;
PubSubClient client(ubidots);

bool mqttConnected;

bool mqtt_initialize() {
  client.setServer(SERVER, PORT);
  while(!client.connect(DEVICE_ID1, TOKEN, "")) {
      Serial.println("MQTT - Connect error");
      return false;
  }

  Serial.println("MQTT - Connect ok");
  mqttConnected = true;
  return true;
}

void sendLuminosidade(float luminosidade) {
  char json[250];
  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"luminosidade\":%02.02f}}}", VARIABLE_LABEL_LUMINOSIDADE, luminosidade, luminosidade);
  client.publish(TOPIC, json) ? Serial.println("Successfully sent power data") : Serial.println("Failed to send power data");
}
