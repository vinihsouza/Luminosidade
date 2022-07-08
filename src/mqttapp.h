#include <PubSubClient.h>

#define TOKEN "BBFF-w7SiUgmq0aA6OMQj7weUT1zzCcjFGw"
#define VARIABLE_LABEL_LUMINOSIDADE "luminosidade"
#define DEVICE_ID1 "62c625ea06c36d000f07877f"
#define SERVER "industrial.api.ubidots.com"
#define PORT 1883
#define TOPIC "/v1.6/devices/esp32_luminosidade"
#define MQTT_INTERVAL_COMMUNICATION 5000

enum MQTT_CONNECTION {
    BOOTING,
    RECONNECTING
};

void sendLuminosidade(float luminosidade);
bool mqtt_connection(MQTT_CONNECTION status);

extern bool mqttConnected;