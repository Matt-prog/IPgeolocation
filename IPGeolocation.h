#ifndef IPGeolocation_h
#define IPGeolocation_h


#include "Arduino.h"
#include <ESP8266WiFi.h>

struct IPGeo {
  IPAddress IP;
  String hostname;
  String continent_code;
  String continent_name;
  String country_code2;
  String country_code3;
  String country_name;
  String country_capital;
  String state_prov;
  String district;
  String city;
  String zipcode;
  float latitude;
  float longitude;
  String geoname_id;
  bool is_eu;
  String calling_code;
  String country_tld;
  String languages;
  String country_flag; //url
  String isp;
  String connection_type;
  String organization;
  String asn;
  
  String currency_name;
  String currency_code;
  String currency_symbol;

  bool is_DST;
  float time_zone;
  float dst_offset;
  String UNIX_time;
};

class IPGeolocation
{
  public:
    IPGeolocation(String Key);
    void key(String Key);
    bool updateData(IPGeo *I);
  private:
    void JsonSerialize(String json, IPGeo *I);
    String _Key;
    String _Response;
};

#endif