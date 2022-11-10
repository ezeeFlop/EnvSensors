#include <Arduino.h>
#include <HomeSpan.h>

#include "Sensors.h"

void setup() {
  Serial.begin(115200);
  homeSpan.setQRID("SPSE");
  homeSpan.setPairingCode("04288826");

  homeSpan.begin(Category::Bridges, "Sensors Bridge");

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Temperature");
  new TempSensor(); 

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Humidity");
  new HumiditySensor(); 

}

void loop() {
  homeSpan.poll();
}