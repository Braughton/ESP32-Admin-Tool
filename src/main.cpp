#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include "settings.hpp"
#include "funciones.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"


void setup(){
  //inicializacion del puerto serial
  Serial.begin(115200);
  //Frecuencia maximapara el ESP32
  setCpuFrequencyMhz(240);
  log("\nInfo: Iniciando Setup");
  settingPines();
  if(!SPIFFS.begin()){
    log("Error:Fallolainicializacion del SPIFFS");
    while(true);
  }
  //Lee la configuracion del wifi
  settingsReadWifi();
  //Configuracion WiFi
  WiFi.disconnect(true);
  delay(1000);
  WiFi_setup();
}
void loop(){
  yield();

  if (wifi_mode==WIFI_MODE_STA)
  {
    wifiLoop(); 
  }
  if (wifi_mode==WIFI_AP)
  {
    wifiAPLoop();
  }
  
  

}
