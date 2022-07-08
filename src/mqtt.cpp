#include "mqttapp.h"
#include "wifiapp.h"

WiFiClient ubidots;
PubSubClient client(ubidots);

bool mqttConnected;
int luminosidade;

bool mqtt_connection(MQTT_CONNECTION status) {
  client.setServer(SERVER, PORT);
  while(!client.connect(DEVICE_ID1, TOKEN, "")) {
    Serial.println("MQTT - Connect error");
    mqttConnected = false;
    return false;
  }
  Serial.println("MQTT - Connect ok");
  mqttConnected = true;
  if (status == RECONNECTING) sendLuminosidade(luminosidade); 
  return true;
}

void sendLuminosidade(float luminosidade) {
  char json[250];
  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"luminosidade\":%02.02f}}}", VARIABLE_LABEL_LUMINOSIDADE, luminosidade, luminosidade);
  if(client.publish(TOPIC, json)) { 
    Serial.println("Successfully sent lightness data");
  } else {
    Serial.println("Failed to send lightness data");
    mqtt_connection(RECONNECTING);
  }
}
