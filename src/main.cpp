#include <../lib/secrets.h>
#include <Ambient.h>
#include <M5StickCPlus.h>
#include <WiFi.h>

WiFiClient client;
Ambient ambient;

void setup() {
  M5.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(1000);

  ambient.begin(AMBIENT_CHANNELID, AMBIENT_WRITEKEY, &client);

  pinMode(32, INPUT);

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 2);
  M5.Lcd.printf("Livingroom Sensor\n");
  M5.Lcd.setCursor(10, 30);
  M5.Lcd.print("Analog:");
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.print("Digital:");
}

uint16_t analogRead_value = 0;
uint16_t digitalRead_value = 0;
uint16_t counter = 0;

void loop() {
  M5.Lcd.setCursor(115, 30);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.printf("%d\n", analogRead_value);
  M5.Lcd.setCursor(115, 50);
  M5.Lcd.printf("%d\n", digitalRead_value);
  analogRead_value = analogRead(33);
  digitalRead_value = digitalRead(32);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setCursor(115, 30);
  M5.Lcd.printf("%d\n", analogRead_value);
  M5.Lcd.setCursor(115, 50);
  M5.Lcd.printf("%d\n", digitalRead_value);

  counter++;
  if (counter == 60) {
    counter = 0;
    ambient.set(1, analogRead_value);
    ambient.set(2, digitalRead_value);
    ambient.send();
  }

  delay(500);
}
