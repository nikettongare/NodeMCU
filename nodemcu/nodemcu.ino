#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "automation-d8b25-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "wKSpaL1no6Y1v9pJlgu0KANZfPzUiaUnX8kIoCII"
#define WIFI_SSID "Styli"
#define WIFI_PASSWORD "lancelot"

void setup() {
  Serial.begin(9600);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("D0", 0);
  Firebase.set("D1", 0);
  Firebase.set("D2", 0);
  Firebase.set("D3", 0);
}

void loop() {
  if (Firebase.failed()) {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    return;
  }


  // For Heart Rate Monotoring
  int sensorValue = analogRead(A0);
  long heartRate = map(sensorValue, 0, 1023, 40, 180);

  Serial.print("Heart Rate: ");
  Serial.println(heartRate);

  Firebase.set("A0", heartRate);

  // For Automation
  toggleBulb(Firebase.getInt("D0"), D0);
  toggleBulb(Firebase.getInt("D1"), D1);
  toggleBulb(Firebase.getInt("D2"), D2);
  toggleBulb(Firebase.getInt("D3"), D3);
}


void firebasereconnect() {
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void toggleBulb(int value, uint8_t port) {
  if (value == 1) {
    digitalWrite(port, LOW);
    Serial.println(port + "BULB ON");
  } else {
    digitalWrite(port, HIGH);
    Serial.println(port + "BULB OFF");
  }
}
