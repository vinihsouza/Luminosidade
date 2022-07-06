#include "wifiapp.h"

bool connecting;
unsigned long wifiLastCommunication;

void wifi_initialize(CONNECTION status) {

    switch(status) {
        case NOT_CONNECTED:
            WiFi.begin(WIFISSID, PASSWORD);
            Serial.println(); Serial.print("Establishing connection to WiFi");
            connecting = true;
        break;
        case CONNECTING:
            if(millis() - wifiLastCommunication > WIFI_INTERVAL_COMMUNICATION) {
                Serial.print(".");
                wifiLastCommunication = millis();
            }
        break;
        case CONNECTED:
            Serial.println("Connected to network");
            connecting = false;
        break;
    }
}
