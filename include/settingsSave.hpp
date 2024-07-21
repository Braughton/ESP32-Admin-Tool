//Guardar estados de los Relays
bool settingsSaveRelays(){
  StaticJsonDocument<500>jsonConfig;
  File file=SPIFFS.open(F("/settingsRelay.json"),"w+");
  if (file)
  {
    jsonConfig["Relay01_status"]=Relay01_status;
    jsonConfig["Relay02_status"]=Relay02_status;
    serializeJsonPretty(jsonConfig,file);
    file.close();
    log(F("Info: Estado de los Relays guardado"));
    serializeJsonPretty(jsonConfig,Serial);
    return true; 
  }else
  {
    log(F("Error:Fallo el guardado del estado de los Relays"));
    return false;
  }
}
