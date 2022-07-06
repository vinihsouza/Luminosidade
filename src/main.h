#include <Arduino.h>

/*Definindo tamanho máximo das tasks*/
#define WIFI_TASK_SIZE 16384
#define MQTT_TASK_SIZE  8192
#define OPER_TASK_SIZE  4096

/*Mapeamento do pino*/ 
#define LUMINOSIDADE  25

/*Inicializando variáveis*/ 
int leituraLuminosidade, luminosidade, minLuminosidade, maxLuminosidade;
unsigned int mqttLastCommunication;
bool sendValue = false;