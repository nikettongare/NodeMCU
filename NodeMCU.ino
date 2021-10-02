// Download FirebaseArduino library from : https://github.com/FirebaseExtended/firebase-arduino and then import this Arduino softwear

// FirebaseArduino now depends on ArduinoJson library instead of containing it's own version of it. Please either use Library Manager or download specific version of the library from github. We recommend that ArduinoJson is at least version 5.13.1

// ESP8266 Core SDK. We recommend using officially tagged releases and it should be at least 2.4.1

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "automation-d8b25-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "wKSpaL1no6Y1v9pJlgu0KANZfPzUiaUnX8kIoCII"
#define WIFI_SSID "Styli"
#define WIFI_PASSWORD ""

void setup()
{
  Serial.begin(115200);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("BULB_STATUS", 0);
  Firebase.set("LIGHT_STATUS", 0);
  Firebase.set("FAN_STATUS", 0);
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
int val1 = 0;
int val2 = 0;
int val3 = 0;
void loop()
{
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    return;
  }

  val1 = Firebase.getInt("BULB_STATUS");

  if (val1 == 1)
  {
    digitalWrite(D2, LOW);
    Serial.println("BULB OFF");
  }
  else
  {
    digitalWrite(D2, HIGH);
    Serial.println("BULB ON");
  }

  val2 = Firebase.getInt("LIGHT_STATUS");

  if (val2 == 1)
  {
    digitalWrite(D2, LOW);
    Serial.println("LIGHT OFF");
  }
  else
  {
    digitalWrite(D2, HIGH);
    Serial.println("LIGHT ON");
  }

  val3 = Firebase.getInt("FAN_STATUS");

  if (val3 == 1)
  {
    digitalWrite(D4, LOW);
    Serial.println("FAN OFF");
  }
  else
  {
    digitalWrite(D4, HIGH);
    Serial.println("FAN ON");
  }
}
