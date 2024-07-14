
//DEFINICION DE PINES DEL ESP32
#define RELAY1 27
#define RELAY2 26
#define WIFILED 12
#define MQTTLED 13

//DEFINICION DE LA VERCION DEL HARDWARE
#define HW "V1.0.0"
//VARIABLES DEL WIFI
bool wifi_staticIP;
char wifi_ssid[30];
char wifi_passw[30];
char wifi_ip_static[15];
char wifi_gateway[15];
char wifi_subnet[15];
char wifi_primaryDNS[15];
char wifi_secondaryDNS[15];
//VARIABLES GENERALES
char id[30];
int bootCount;
//VARIABLES AP
bool ap_accessPoint;
char ap_nameap[31];
char ap_passwordap[63];
int ap_canalap;
int ap_hiddenap;
int ap_connetap;
//Miselaneos
uint8_t ip[4];

