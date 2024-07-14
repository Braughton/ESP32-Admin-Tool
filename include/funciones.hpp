#include "LedBlink.hpp"
void log(String s){
  Serial.println(s);
}
String platform(){
  #ifdef ARDUINO_ESP32_DEV
  return "ESP32";
  #endif
}
IPAddress CharToIP(const char *str){
  sscanf(str,"%hhu.%hhu.%hhu.%hhu",&ip[0],&ip[1],&ip[2],&ip[3]);
  return IPAddress(ip[0],ip[1],ip[2],ip[3]);
}
String ipStr(const IPAddress &ip){
  String sFn ="";
  for (byte bFn = 0; bFn < 3; bFn++)
  {
    sFn+=String((ip>>(8*bFn))&0xFF) + ".";
  }
  sFn+=String(((ip>>8*3))&0xFF) + "." ;
  return sFn;
  
}
String hexStr(const unsigned long &h,const byte &l =8){
  String s;
  s=String(h,HEX);
  s.toUpperCase();
  s=("00000000"+s).substring(s.length()+8-l);
  return s;
}
String idUnique(){
  char idunique[15];
  uint64_t chipid =ESP.getEfuseMac();
  uint16_t chip=(uint16_t)(chipid>>32);
  snprintf(idunique,15,"%04x",chip);
  return idunique;
}
String deviceID(){
  return String(platform())+hexStr(ESP.getEfuseMac())+String(idUnique());
}
//Configuracion de salidas
void settingPines(){
  pinMode(WIFILED,OUTPUT);
  pinMode(MQTTLED,OUTPUT);
  pinMode(RELAY1,OUTPUT);
  pinMode(RELAY2,OUTPUT);
  digitalWrite(RELAY1,LOW);
  digitalWrite(RELAY2,LOW);
  digitalWrite(WIFILED,LOW);
  digitalWrite(MQTTLED,LOW);
}