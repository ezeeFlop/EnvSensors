#include <homespan.h>

#include "DHTesp.h"  // Click here to get the library: http://librarymanager/All#DHTesp

#define DHTPIN 4    // Changer le pin sur lequel est branché le DHT
#define DHTTYPE DHTesp::DHT22  // DHT 2  (AM2302)

DHTesp dht;

struct TempSensor : Service::TemperatureSensor {     // A standalone Temperature sensor

  SpanCharacteristic *temp;                         // reference to the Current Temperature Characteristic
  
  TempSensor() : Service::TemperatureSensor(){       // constructor() method
    dht.setup(DHTPIN, DHTTYPE);

    if (dht.getStatus() != 0) {
      LOG0("DHT22 error status: " + String(dht.getStatusString()));
    }
    float temperature = dht.getTemperature();

    temp = new Characteristic::CurrentTemperature(temperature);        // instantiate the Current Temperature Characteristic

    LOG0("Configuring Temperature Sensor");           // initialization message

  } // end constructor

  void loop(){

    if(temp->timeVal()>5000){                               // check time elapsed since last update and proceed only if greater than 5 seconds
      float temperature = dht.getTemperature();
      
      temp->setVal(temperature);                            // set the new temperature; this generates an Event Notification and also resets the elapsed time
      
      LOG1("Temperature Update %s\n", temperature);
    }
    
  } // loop
  
};

//////////////////////////////////

struct HumiditySensor : Service::HumiditySensor {     // A standalone Air Quality sensor

  // An Air Quality Sensor is similar to a Temperature Sensor except that it supports a wide variety of measurements.
  // We will use three of them.  The first is required, the second two are optional.

  SpanCharacteristic *humidity;                 // reference to the Air Quality Characteristic, which is an integer from 0 to 5
  
  HumiditySensor() : Service::HumiditySensor(){       // constructor() method
    dht.setup(DHTPIN, DHTTYPE);

    if (dht.getStatus() != 0) {
      LOG0("DHT22 error status: " + String(dht.getStatusString()));
    }
    humidity = new Characteristic::CurrentRelativeHumidity(dht.getHumidity());  // instantiate the Air Quality Characteristic and set initial value to 1

    LOG0("Configuring Humidity Sensor");   // initialization message

  } // end constructor

  void loop(){
     if(humidity->timeVal()>5000){ 
      float h = dht.getHumidity();
      humidity->setVal(h);
     }
  } 

};