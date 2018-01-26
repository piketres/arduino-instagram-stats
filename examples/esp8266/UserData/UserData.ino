/*******************************************************************
 *  An example of usisng the InstagramStats library to get
 *  info on a given user.
 *  route
 *
 *  Written by Brian Lough
 *  https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA
 *******************************************************************/

 // ----------------------------
 // Standard Libraries - Already Installed if you have ESP8266 set up
 // ----------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include "InstagramStats.h"
#include "JsonStreamingParser.h"

//------- Replace the following! ------
char ssid[] = "SSID";       // your network SSID (name)
char password[] = "PASSWORD";  // your network key

WiFiClientSecure client;
InstagramStats instaStats(client);

unsigned long delayBetweenChecks = 60000; //mean time between api requests
unsigned long whenDueToCheck = 0;

//Inputs
String userName = "brian_lough"; // from their instagram url https://www.instagram.com/brian_lough/


void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void getInstagramStatsForUser() {
  Serial.println("Getting instagram user stats for " + userName );
  InstagramUserStats response = instaStats.getUserStats(userName);
  Serial.println("Response:");
  Serial.print("Number of followers: ");
  Serial.print(response.followedByCount);
}

void loop() {
  unsigned long timeNow = millis();
  if ((timeNow > whenDueToCheck))  {
    getInstagramStatsForUser();
    whenDueToCheck = timeNow + delayBetweenChecks;
  }
}
