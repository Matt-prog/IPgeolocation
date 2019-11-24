#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "IPGeolocation.h"

const char *host = "api.ipgeolocation.io";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
WiFiClientSecure httpsClient;

IPGeolocation::IPGeolocation(String Key){
  _Key = Key;
}

void IPGeolocation::key(String Key){
  _Key = Key;
}

bool IPGeolocation::updateData(IPGeo *I){
  if(_Key.length() == 0) return false;
  httpsClient.setInsecure();
  httpsClient.setTimeout(5000); // 5 Seconds
  
  if(!httpsClient.connect(host, httpsPort)) return false;

  httpsClient.print(String("GET ") + "/ipgeo?apiKey=" + _Key + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  
  String _Response;
  while (httpsClient.connected()) {
    _Response = httpsClient.readStringUntil('\n');
    if (_Response.charAt(0) == '{') break;
  }
  JsonSerialize(_Response, I);
  return true;
}

void IPGeolocation::JsonSerialize(String json, IPGeo *I){
  int json_length = json.length();
  byte object = 0; //0 = none, 1 = currency, 2 = time_zone, 3 = unknown
  bool key_started = false;
  bool key_end = false;
  bool value_started = false;
  bool com_en = false;
  String key = "";
  String value = "";
  for(int i = 0; i < json_length; i++){
    if(json.charAt(i) == '"' || (key_started && key_end && !value_started && json.charAt(i) == ':' && json.charAt(i+1) != '"' && json.charAt(i+1) != '{') || (key_started && key_end && value_started && !com_en && (json.charAt(i) == ',' || json.charAt(i) == '}'))){
      if(value_started){ //end of value found
        key_started = false;
        key_end = false;
        value_started = false;
          if(key == "ip") I->IP.fromString(value);
          else if(key == "hostname") I->hostname = value;
          else if(key == "continent_code") I->continent_code = value;
          else if(key == "continent_name") I->continent_name = value;
          else if(key == "country_code2") I->country_code2 = value;
          else if(key == "country_code3") I->country_code3 = value;
          else if(key == "country_name") I->country_name = value;
          else if(key == "country_capital") I->country_capital = value;
          else if(key == "state_prov") I->state_prov = value;
          else if(key == "district") I->district = value;
          else if(key == "city") I->city = value;
          else if(key == "zipcode") I->zipcode = value;
          else if(key == "latitude") I->latitude = value.toFloat();
          else if(key == "longitude") I->longitude = value.toFloat();
          else if(key == "geoname_id") I->geoname_id = value;
          else if(key == "is_eu") I->is_eu = (value == "true");
          else if(key == "calling_code") I->calling_code = value;
          else if(key == "country_tld") I->country_tld = value;
          else if(key == "languages") I->languages = value;
          else if(key == "country_flag") I->country_flag = value;
          else if(key == "isp") I->isp = value;
          else if(key == "connection_type") I->connection_type = value;
          else if(key == "organization") I->organization = value;
          else if(key == "asn") I->asn = value;
          else if(key == "name") I->currency_name = value;
          else if(key == "code") I->currency_code = value;
          else if(key == "symbol") I->currency_symbol = value;
          else if(key == "offset") I->time_zone = value.toFloat();
          else if(key == "dst_savings") I->dst_offset = value.toFloat();
          else if(key == "is_dst") I->is_DST = (value == "true");
          else if(key == "current_time_unix") I->UNIX_time = value;
      }
      else if(key_end){
        value_started = true;
        value = "";
        com_en = json.charAt(i) == '"';
      }
      else if(key_started) key_end = true;
      else{
        key_started = true;
        key = "";
      }
    }
    else if(json.charAt(i) == '{' && key_end && !value_started){ //new object found
      if(key == "time_zone") object = 2;
      else if(key == "currency") object = 1;
      else object = 3;
      key_end = false;
      key_started = false;
    }
    else if(json.charAt(i) == '}'){
      if(object == 0){
        break; //end of json
      }
      object = 0; //end of object
    }
    else if(key_started && !key_end){
      key += json.charAt(i);
    }
    else if(key_started && key_end && value_started){
      value += json.charAt(i);
    }
  }
}
