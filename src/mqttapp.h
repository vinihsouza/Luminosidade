#include <PubSubClient.h>

#define TOKEN "BBFF-PlEgfKJAI3HyKUUobiE6o7XWU5m61S"
#define VARIABLE_LABEL_LUMINOSIDADE "luminosidade"
#define DEVICE_ID1 "62b26a42e41edb35493f96cc"
#define SERVER "industrial.api.ubidots.com"
#define PORT 1883
#define TOPIC "/v1.6/devices/esp32"
#define MQTT_INTERVAL_COMMUNICATION 5000

void sendLuminosidade(float luminosidade);
bool mqtt_initialize();

extern bool mqttConnected;