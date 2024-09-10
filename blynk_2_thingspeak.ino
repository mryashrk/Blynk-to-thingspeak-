#define BLYNK_TEMPLATE_ID "TMPL3082tPByg"
#define BLYNK_TEMPLATE_NAME "blynk to thingspeak"
#define BLYNK_AUTH_TOKEN "wwKou1VyOuaGno5XthTg2TcR7xkNutQ1"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ThingSpeak.h>
#include <HTTPClient.h>

String host = "api.thingspeak.com";
int httpPort = 80;
String url1 = "/update?api_key=HTILMCL2UKUF93JI&field1=";
String url2 = "/update?api_key=HTILMCL2UKUF93JI&field2=";

unsigned long myChannelNumber = 2650752;
const char* myWriteAPIKey = "HTILMCL2UKUF93JI";

HTTPClient http;
WiFiClient client;

// Your WiFi credentials.
char ssid[] = "Redmi 9 Prime";
char pass[] = "00000000";

BLYNK_WRITE(V0)
{
  int value1 = param.asInt();
  Serial.print("value 1 is = ");
  Serial.println(value1);

  String link1 = url1 + (String) value1;
  http.begin(client, host, httpPort, link1);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("HTTP GET failed");
  }
  http.end();
}

BLYNK_WRITE(V1)
{
  int value2 = param.asInt();
  Serial.print("value 2 is = ");
  Serial.println(value2);

  String link2 = url2 + (String) value2;
  http.begin(client, host, httpPort, link2);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("HTTP GET failed");
  }
  http.end();
}

BLYNK_WRITE(V2)
{
  int value3 = param.asInt();
  Serial.print("value 3 is = ");
  Serial.println(value3);

  ThingSpeak.setField(3, value3);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Update successful");
  } else {
    Serial.print("Update failed. Error code: ");
    Serial.println(x);
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  ThingSpeak.begin(client);
}

void loop() {
  Blynk.run();
}

