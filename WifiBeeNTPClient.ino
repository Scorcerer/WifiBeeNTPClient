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
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//  Serial.println("Starting UDP");
//  udp.begin(localPort);
//  Serial.print("Local port: ");
//  Serial.println(udp.localPort());
  
  timeClient.begin();
  
}

void loop()
{
  //get a random server from the pool
  timeClient.update();

  unsigned long epoch = timeClient.getEpochTime();
  Serial.print("Unix time = ");

  // print Unix time:
  Serial.println(epoch);


  // print the hour, minute and second:
  Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
  Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
  Serial.print(':');
  if ( ((epoch % 3600) / 60) < 10 ) {
    // In the first 10 minutes of each hour, we'll want a leading '0'
    Serial.print('0');
  }
  Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
  Serial.print(':');
  if ( (epoch % 60) < 10 ) {
    // In the first 10 seconds of each minute, we'll want a leading '0'
    Serial.print('0');
  }
  Serial.println(epoch % 60); // print the second

  // wait a second before spitting time again
  delay(1000);
}
