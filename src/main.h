#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*Definindo tamanho máximo das tasks*/
#define WIFI_TASK_SIZE 16384
#define MQTT_TASK_SIZE  8192
#define OPER_TASK_SIZE  4096

#define LUMENS000   80
#define LUMENS042  512
#define LUMENS170  170
#define LUMENS999 2786

/*Mapeamento do pino*/ 
#define LUMINOSIDADE  35

/*Inicializando variáveis*/ 
extern int luminosidade;
unsigned int mqttLastCommunication;
int leituraLuminosidade, minLuminosidade, maxLuminosidade;
bool sendValue = false;

/*Declarando funções*/ 
void vTaskWIFI(void *pvParameters);
void vTaskMQTT(void *pvParameters);
void vTaskOPER(void *pvParameters);
