#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
const byte DNSSERVER_PORT=53;
DNSServer dnsServer;
IPAddress apIP(192,168,4,1);
IPAddress netMsk(255,255,255,0);
int wifi_mode = WIFI_STA;
unsigned long previousMillisWIFI=0;
unsigned long intervalWIFI=30000; 
const char *esp_hostname=id;

void startAP(){
  log("Info: Iniciando Modo AP");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.softAPConfig(apIP,apIP,netMsk);
  WiFi.setHostname(deviceID().c_str());
  WiFi.softAP(ap_nameap,ap_passwordap,ap_canalap,ap_hiddenap,ap_connetap);
  log("Info: WiFi AP"+deviceID()+"-IP"+ipStr(WiFi.softAPIP()));
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNSSERVER_PORT,"*",apIP);
  wifi_mode=WIFI_AP;
}
void startClient(){
  if(wifi_staticIP){
    if(!WiFi.config(CharToIP(wifi_ip_static),CharToIP(wifi_gateway),CharToIP(wifi_subnet),CharToIP(wifi_primaryDNS),CharToIP(wifi_secondaryDNS))){
      log("Error: Fallo al conectar el modo Estacion");
    }
  }
  WiFi.hostname(deviceID());
  WiFi.begin(wifi_ssid,wifi_passw);
  log("Info: Conectando WiFi " + String(wifi_ssid));
  delay(50);
  byte b=0;
  while (WiFi.status() !=WL_CONNECTED && b<60){
    b++;
    log("Warning: Intentando conexxion WiFi...");
    delay(500);
    blinkSingle(100,WIFILED);
  }
  if (WiFi.status()==WL_CONNECTED)
  {
    log("Info: WiFi conectado("+String(WiFi.RSSI())+") IP"+ipStr(WiFi.localIP()));
    blinkRandomSingle(10,100,WIFILED);
    delay(100);
  }else{
    log(F("Error: WiFi no esta conectado"));
    blinkRandomSingle(10,100,WIFILED);
    delay(100);
  }
}
void WiFi_setup(){
  WiFi.disconnect();
  //Cundo el ap esta activo
  if (ap_accessPoint){
    startAP();
    log("Info: WiFi Modo AP");
  }
  //Modo cliente
  else{
    WiFi.mode(WIFI_STA);
    wifi_mode=WIFI_STA;
    startClient();
    log("Info: WiFi en Modo Estacion");
  }
    if (wifi_mode==WIFI_STA||wifi_mode==WIFI_AP){
    if (MDNS.begin(esp_hostname)){
      MDNS.addService("http","tcp",80);
    }
  }
}
void wifiLoop(){
  unsigned long currentMillis=millis();
  if(WiFi.status()!=WL_CONNECTED && (currentMillis-previousMillisWIFI>=intervalWIFI)){
    blinkSingle(100,WIFILED);
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillisWIFI=currentMillis;
  }else{
    blinkSingleAsy(10,500,WIFILED);
  }
}
void wifiAPLoop(){
  blinkRandomSingle(50,100,WIFILED);
  dnsServer.processNextRequest();
}