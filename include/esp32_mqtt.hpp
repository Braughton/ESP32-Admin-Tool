#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttclient(espClient); 

char topico[150];
String mqtt_data ="";
long lastMqttReconnectAttempt=0;
long lastMsg=0;
void callback(char *topic,byte *payload,unsigned int length);
String Json();

//Coneccion al Broker
bool mqtt_connect(){
  mqttclient.setServer(mqtt_server,mqtt_port);
  mqttclient.setCallback(callback);
  log("Info: Conectando al Broker MQTT");

  if (mqttclient.connect(mqtt_id,mqtt_user,mqtt_passw))
  {
    log("info:Conectado al Broker MQTT");
    String topico_suscribe = String(mqtt_user)+"/"+mqtt_id+"/command";
    topico_suscribe.toCharArray(topico,150);
    mqttclient.subscribe(topico);
    topico_suscribe.toCharArray(topico,150);
    mqttclient.publish(topico,"ok");
  }else{
    log("Error: failed, rc="+mqttclient.state());
    return (0);
  }
  return (1); 
}
//Control de mensajes resibidos
void callback(char *topic,byte *payload,unsigned int length){
  String mensaje="";
  String str_topic(topic);
  for (uint16_t i = 0; i < length; i++)
  {
    mensaje+=(char)payload[i];
    mqttRX();
  }
  mensaje.trim();
  DynamicJsonDocument jsonDoc(300);
  deserializeJson(jsonDoc,mensaje);
  if (jsonDoc["RELAY1"]=="on")
  {
    setOnSingle(RELAY1);
    Relay01_status=HIGH;
    settingsSaveRelays();
  }else if (jsonDoc["RELAY1"]=="off")
  {
    setOnSingle(RELAY1);
    Relay01_status=LOW;
    settingsSaveRelays();
  }else if (jsonDoc["RELAY2"]=="on")
  {
    setOnSingle(RELAY2);
    Relay02_status=HIGH;
    settingsSaveRelays();
  }else if (jsonDoc["RELAY2"]=="off");
  {
    setOnSingle(RELAY2);
    Relay02_status=LOW;
    settingsSaveRelays();
  }
  
  log("Info: Topico-->"+str_topic);
  log("Info: Mensaje-->"+mensaje);
  serializeJsonPretty(jsonDoc,Serial);

}

//control de salida de mensajes
void mqtt_publish(){
  
  String topic= String(mqtt_user)+"/"+mqtt_id+"/values";
  mqtt_data=Json();
  mqttclient.publish(topic.c_str(),mqtt_data.c_str());
  mqtt_data="";
  mqttTX();
}

String Json(){
  String response;
  DynamicJsonDocument jsonDoc(3000);
  jsonDoc["wifi_dbm"]=WiFi.status()==WL_CONNECTED?String(WiFi.RSSI()):F("0");
  jsonDoc["wifi_percent"]=WiFi.status()==WL_CONNECTED?String(getRSSIasQuality(WiFi.RSSI())):F("0");
  jsonDoc["temp_cpu"]=String(TempCPUValue());
  jsonDoc["ram_available"]=String(ESP.getFreeHeap()*100/ESP.getHeapSize());
  jsonDoc["flash_used"]=String(round(SPIFFS.usedBytes()*100/SPIFFS.totalBytes()),0);
//  jsonDoc["relay1"]=String(Relay1Status?"true":"false");
//  jsonDoc["relay2"]=String(Relay2Status?"true":"false");

  serializeJson(jsonDoc,response);
  return response;
}

//MQTT main loop
void mqttloop(){
  if (mqtt_enabled)
  {
    if (!mqttclient.connected())
    {
      long now=millis();
      if ((now<60000)||((now-lastMqttReconnectAttempt)>120000))
      {
        lastMqttReconnectAttempt=now;
        if (mqtt_connect())
        {
          lastMqttReconnectAttempt=0;
        }
        setOnSingle(MQTTLED);
      }
      
    }else{
      mqttclient.loop();
      setOffSingle(MQTTLED);
    }
    
  }
  
}
