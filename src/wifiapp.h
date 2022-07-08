#include <WiFi.h>
/*Descomentar os comandos abaixo e em "" colocar o nome da sua rede e abaixo a senha.*/

//#define WIFISSID "Sua rede"    //SSID
//#define PASSWORD "Sua senha"   //PASSWORD
#define HOSTNAME "FitSorocaba"
#define WIFI_INTERVAL_COMMUNICATION 100

enum CONNECTION {
    NOT_CONNECTED,
    CONNECTING,
    CONNECTED
};

extern bool connecting;
extern unsigned long wifiLastCommunication;

void wifi_initialize(CONNECTION status);
