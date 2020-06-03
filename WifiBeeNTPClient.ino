#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "kvs";  //  your network SSID (name)
char pass[] = "kluseczki##321";       // your network password

const long utcOffsetInSeconds = 7200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pl.pool.ntp.org", utcOffsetInSeconds);


void setup()
{
  Serial.begin(115200);

  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  timeClient.begin();
  
}

void loop()
{
  timeClient.update();

  unsigned long epoch = timeClient.getEpochTime();
  
  Serial.print("UNX");
  Serial.println(epoch);
  
  delay(30000);
}
