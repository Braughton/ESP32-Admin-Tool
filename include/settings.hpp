
//DEFINICION DE PINES DEL ESP32
#define RELAY1 27
#define RELAY2 26
#define WIFILED 12
#define MQTTLED 13

//DEFINICION DE LA VERCION DEL HARDWARE
#define HW "V1.0.0"
//VARIABLES GENERALES
char id[30];
int bootCount;
//VARIABLES DEL WIFI
bool wifi_staticIP;
char wifi_ssid[30];
char wifi_passw[30];
char wifi_ip_static[15];
char wifi_gateway[15];
char wifi_subnet[15];
char wifi_primaryDNS[15];
char wifi_secondaryDNS[15];

//VARIABLES AP
bool ap_accessPoint;
char ap_nameap[31];
char ap_passwordap[63];
int ap_canalap;
int ap_hiddenap;
int ap_connetap;
//Variables MQTT
bool mqtt_enabled;
char mqtt_user[30];
char mqtt_id[30];
char mqtt_passw[30];
char mqtt_server[39];
int mqtt_port;
int mqtt_time;
//Miselaneos
uint8_t ip[4];
float TempCPU;
//Relay
bool Relay01_status;
bool Relay02_status;