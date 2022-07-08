/* =======================================================================
   Envio de luminosidade, com deepSleep e FreeRTOS

   ESP-WROOM-32U
   Board: DevKitV1
   Compilador: VS Code (Ext PlatformIO)

   Autor: Eng. Vinícius Souza -> /in/eng-viniciussouza/
   Data:  Julho de 2022
======================================================================= */

#include "main.h"
#include "wifiapp.h"
#include "mqttapp.h"

TaskHandle_t taskMqtt = NULL, taskWifi = NULL, taskOper = NULL;

void setup() {
  Serial.begin(115200);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, HIGH);
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
  mqtt_connection(BOOTING);
  for ( ;; ) {
    if((millis() - mqttLastCommunication > MQTT_INTERVAL_COMMUNICATION) && mqttConnected && sendValue) {
      sendLuminosidade(luminosidade);
      Serial.println("Leitura luminosidade: "); Serial.println(leituraLuminosidade);
      Serial.println("luminosidade: "); Serial.println(luminosidade);
      mqttLastCommunication = millis();
      sendValue = false;
      if(leituraLuminosidade < LUMENS999) {
        Serial.println("Entrando em modo deep sleep");
        esp_deep_sleep_start();
      }
    }
    else if (!mqttConnected) mqtt_connection(BOOTING);
  }
}

void vTaskOPER(void *pvParameters) {
  disableCore0WDT();
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, HIGH);
  analogReadResolution(12);
  analogSetAttenuation(ADC_6db);
  pinMode(LUMINOSIDADE, INPUT); 
  for ( ;; ) {
    leituraLuminosidade = analogRead(LUMINOSIDADE);
    if(leituraLuminosidade > maxLuminosidade || leituraLuminosidade < minLuminosidade) {
      maxLuminosidade = leituraLuminosidade + 150;
      minLuminosidade = leituraLuminosidade - 150;
      if     (leituraLuminosidade >= LUMENS999) luminosidade = leituraLuminosidade / 4.095;
      else if(leituraLuminosidade >= LUMENS170) luminosidade = leituraLuminosidade / 5.353;
      else if(leituraLuminosidade >= LUMENS042) luminosidade = leituraLuminosidade / 12.19;
      else if(leituraLuminosidade >= LUMENS000) luminosidade = leituraLuminosidade / 30.00;
      sendValue = true;
    }
  }
}
