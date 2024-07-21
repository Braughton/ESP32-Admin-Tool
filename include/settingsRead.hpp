//Leer configruaciones del WIFI
bool settingsReadWifi(){
  StaticJsonDocument<500> jsonConfig;
  File file=SPIFFS.open("/SettingConfigWifi.json","r");
  if(deserializeJson(jsonConfig,file)){
    settingResetWiFi();
    log("Error: Fallo la lectura de la configuracion de WiFi, tomando valores por defecto");
    return false;
  }else{
    //General
    strlcpy(id,jsonConfig["id"],sizeof(id));
    bootCount = jsonConfig["boot"];
    //Cliente
    wifi_staticIP = jsonConfig[wifi_staticIP];
    strlcpy(wifi_ssid,jsonConfig["wifi_ssid"],sizeof(wifi_ssid));
    strlcpy(wifi_passw,jsonConfig["wifi_passw"],sizeof(wifi_passw));
    strlcpy(wifi_ip_static,jsonConfig["wifi_ip_static"],sizeof(wifi_ip_static));
    strlcpy(wifi_gateway,jsonConfig["wifi_gateway"],sizeof(wifi_gateway));
    strlcpy(wifi_subnet,jsonConfig["wifi_subnet"],sizeof(wifi_subnet));
    strlcpy(wifi_primaryDNS,jsonConfig["wifi_primaryDNS"],sizeof(wifi_primaryDNS));
    strlcpy(wifi_secondaryDNS,jsonConfig["wifi_secondaryDNS"],sizeof(wifi_secondaryDNS));
    //AP
    ap_accessPoint = jsonConfig["ap_accessPoint"];
    strlcpy(ap_nameap,jsonConfig[ap_nameap],sizeof(ap_nameap));
    strlcpy(ap_passwordap,jsonConfig[ap_passwordap],sizeof(ap_passwordap));
    ap_canalap = jsonConfig["ap_canalap"];
    ap_hiddenap = jsonConfig["ap_hidden"];
    ap_connetap = jsonConfig["ap_connet"];
    file.close();
    log("info: Lectura configuracion de WiFi correct");
    return true;
  }
}
//Leer configuraciones del MQTT
bool settingsReadMQTT(){
  StaticJsonDocument<500>jsonConfig;
  File file=SPIFFS.open(F("/settingsMQTT.json"),"r");
  if (deserializeJson(jsonConfig,file))
  {
    settingsResetMQTT();
    log(F("Error: fallo la lectura de la configuracion MQTT,tomando valores por defecto"));
    return false;
  }
  else{
    strlcpy(mqtt_user,jsonConfig["mqtt_user"],sizeof(mqtt_user));
    strlcpy(mqtt_passw,jsonConfig["mqtt_passw"],sizeof(mqtt_passw));
    strlcpy(mqtt_server,jsonConfig["mqtt_server"],sizeof(mqtt_server));
    strlcpy(mqtt_id,jsonConfig["mqtt_id"],sizeof(mqtt_id));
    mqtt_time =jsonConfig["mqtt_time"];
    mqtt_port=jsonConfig["mqtt_port"];
    mqtt_enabled=jsonConfig["mqtt_enabled"];
    file.close();
    log("Info: Lectura de configuracion MQTT correcta");
    return true;
  }
  
}
//Leer estados de los Relays
bool settingsReadRelay(){
   StaticJsonDocument<500>jsonConfig;
  File file=SPIFFS.open(F("/settingsRelay.json"),"r");
  if (deserializeJson(jsonConfig,file))
  {
    settingsResetRelay();
    log(F("Error: fallo la lectura de la configuracion de los Relay,tomando valores por defecto"));
    return false;
  }else{
    Relay01_status=jsonConfig["Relay01_status"];
    Relay02_status=jsonConfig["Relay02_status"];
    file.close();
    log("Info:Lectura de los Relays correcta");
    return true;
  }

}