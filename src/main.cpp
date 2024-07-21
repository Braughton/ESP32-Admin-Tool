//Incluyendo librerias
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include "settings.hpp"
#include "funciones.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"
#include "esp32_mqtt.hpp"


void setup(){
  //inicializacion del puerto serial
  Serial.begin(115200);
  //Frecuencia maximapara el ESP32
  setCpuFrequencyMhz(240);
  log("\nInfo: Iniciando Setup");
  settingPines();
  if(!SPIFFS.begin()){
    log(F("Error:Fallolainicializacion del SPIFFS"));
    while(true);
  }
  //Lee el estado de los Relay
  settingsReadRelay();
  //configuracion de relays con los estados leidos
  setOnOffSingle(RELAY1,Relay01_status);
  setOnOffSingle(RELAY2,Relay02_status);
  //Lee la configuracion del wifi
  settingsReadWifi();
  //Configuracion WiFi
  WiFi.disconnect(true);
  delay(1000);
  WiFi_setup();
  settingsReadMQTT();
}

void loop(){
  yield();
//WiFi
  if (wifi_mode==WIFI_STA)
  {
    wifiLoop(); 
  }
  else if (wifi_mode==WIFI_AP)
  {
    wifiAPLoop();
  }
//MQTT
  if ((WiFi.status()==WL_CONNECTED)&&(wifi_mode==WIFI_STA))
  {
    if (mqtt_server!=0)
    {
      mqttloop();
      if (mqttclient.connected())
      {
        if (millis()-lastMsg>mqtt_time)
        {
          lastMsg=millis();
          mqtt_publish();
        }
        
      }
      
    }
    
  }
  

}
