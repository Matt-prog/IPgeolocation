/*
 * Sample sketch that sends request to ipgeolocation.io and
 * receives useful informations such as: public IP, city name, time zone, ...
 */

#include <ESP8266WiFi.h>
#include <IPGeolocation.h>

#define SSID "your-ssid"
#define PASS  "your-password"

//To get this API key, you have to register at https://ipgeolocation.io/
#define GEO_API_KEY "your-geo-api-key"

IPGeolocation geo(GEO_API_KEY); //IPgeolocation object
IPGeo IPG; //IPgeolocation structure

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println("Connecting to ipgeolocation.io .... ");
  //Updating data from IPgeolocation server
  if(geo.updateData(&IPG)){
    Serial.println("DONE");
    Serial.println("Received data:");
    Serial.print("IP: "); Serial.println(IPG.IP.toString());
    Serial.print("Hostname: "); Serial.println(IPG.hostname);
    Serial.print("Continent code: "); Serial.println(IPG.continent_code);
    Serial.print("Continent name: "); Serial.println(IPG.continent_name);
    Serial.print("Country code2: "); Serial.println(IPG.country_code2);
    Serial.print("Country code3: "); Serial.println(IPG.country_code3);
    Serial.print("Country name: "); Serial.println(IPG.country_name);
    Serial.print("Country capital: "); Serial.println(IPG.country_capital);
    Serial.print("State provider: "); Serial.println(IPG.state_prov);
    Serial.print("District: "); Serial.println(IPG.district);
    Serial.print("City: "); Serial.println(IPG.city);
    Serial.print("Zipcode: "); Serial.println(IPG.zipcode);
    Serial.print("Latitude: "); Serial.println(IPG.latitude);
    Serial.print("Longitude: "); Serial.println(IPG.longitude);
    Serial.print("Geoname ID: "); Serial.println(IPG.geoname_id);
    Serial.print("Is EU: "); Serial.println(IPG.is_eu?"true":"false");
    Serial.print("Calling code: "); Serial.println(IPG.calling_code);
    Serial.print("Country TLD: "); Serial.println(IPG.country_tld);
    Serial.print("Languages: "); Serial.println(IPG.languages);
    Serial.print("Country flag URL: "); Serial.println(IPG.country_flag);
    Serial.print("Isp: "); Serial.println(IPG.isp);
    Serial.print("Connection type: "); Serial.println(IPG.connection_type);
    Serial.print("Organization: "); Serial.println(IPG.organization);
    Serial.print("AS number: "); Serial.println(IPG.asn);
    Serial.print("Currency name: "); Serial.println(IPG.currency_name);
    Serial.print("Currency code: "); Serial.println(IPG.currency_code);
    Serial.print("Currency symbol: "); Serial.println(IPG.currency_symbol);
    Serial.print("Is DST: "); Serial.println(IPG.is_DST?"true":"false");
    Serial.print("DST offset: "); Serial.println(IPG.dst_offset);
    Serial.print("Time zone: "); Serial.println(IPG.time_zone);
    Serial.print("UNIX time: "); Serial.println(IPG.UNIX_time);
  }
  else{
    Serial.println("FAILED");
  }
}

void loop() {
  //Nothing to do here

}
