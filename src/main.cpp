#include "main.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifiapp.h"
#include "mqttapp.h"

TaskHandle_t taskMqtt = NULL, taskWifi = NULL, taskOper = NULL;

void vTaskWIFI(void *pvParameters);
void vTaskMQTT(void *pvParameters);
void vTaskOPER(void *pvParameters);

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(vTaskWIFI, "WIFI TASK", WIFI_TASK_SIZE, NULL, 5, &taskWifi, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskOPER, "OPER TASK", OPER_TASK_SIZE, NULL, 5, &taskOper, PRO_CPU_NUM);
}

void loop() {
  vTaskDelay(3000);
}

void vTaskWIFI(void *pvParameters) {
  wifi_initialize(NOT_CONNECTED);
  for ( ;; ) {
    if(!connecting && WiFi.status() != WL_CONNECTED) {
      wifi_initialize(NOT_CONNECTED);
    } 
    else if (connecting && WiFi.status() != WL_CONNECTED) {
      wifi_initialize(CONNECTING);
    } 
    else if (connecting && WiFi.status() == WL_CONNECTED) {
      wifi_initialize(CONNECTED);
      xTaskCreatePinnedToCore(vTaskMQTT, "MQTT TASK", MQTT_TASK_SIZE, NULL, 5, &taskMqtt, APP_CPU_NUM);
    }
  }
}

void vTaskMQTT(void *pvParameters) {
  mqtt_initialize();
  for ( ;; ) {
    if((millis() - mqttLastCommunication > MQTT_INTERVAL_COMMUNICATION) && mqttConnected && sendValue) {
      sendLuminosidade(luminosidade);
      mqttLastCommunication = millis();
      sendValue = !sendValue;
    }
  }
}

void vTaskOPER(void *pvParameters) {
  disableCore0WDT();
  analogReadResolution(12);
  analogSetAttenuation(ADC_6db);
  pinMode(LUMINOSIDADE, INPUT);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_25, ESP_EXT1_WAKEUP_ANY_HIGH);
  for ( ;; ) {
    leituraLuminosidade = analogRead(LUMINOSIDADE);
    if(leituraLuminosidade >= maxLuminosidade || leituraLuminosidade <= minLuminosidade) {
      maxLuminosidade = leituraLuminosidade + 20;
      minLuminosidade = leituraLuminosidade - 20;
      luminosidade = leituraLuminosidade / 15;
      sendValue = true;
    }
    if(!sendValue) esp_deep_sleep_start();
  }
}
