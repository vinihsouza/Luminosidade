#include <WiFi.h>

#define WIFISSID "2.4GHz_MINHACLARO"
#define PASSWORD "Todesacocheio2"
#define WIFI_INTERVAL_COMMUNICATION 100

enum CONNECTION {
    NOT_CONNECTED,
    CONNECTING,
    CONNECTED
};

extern bool connecting;
extern unsigned long wifiLastCommunication;

void wifi_initialize(CONNECTION status);
