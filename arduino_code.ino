/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// Data wire is connected to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// How many sensors are on the bus
int numberOfSensors; 

// Netio rs232 wired to pins 0(rx) and 1(tx)
SoftwareSerial netio(0, 1, 1);

// enable this when debugging. It will print some extra data to the serial monitor
bool isDebugging = false;

void setup(void)
{
  // Start serial communication for debugging purposes
  if (isDebugging) {
    Serial.begin(9600);
    while (!Serial)
      continue;
  }

  // Start serial uplink to Netio PDU
  netio.begin(9600);

  // Start up the library
  sensors.begin();

  // Grab a count of sensors seen on the wire
  numberOfSensors = sensors.getDeviceCount();

  // Send a carriage return which will trigger the Netio's Lua monitoring script
  netio.write(0xd);
}

void loop(void){ 
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 

  if (isDebugging) {
    Serial.print("Number of sensors on bus: ");
    Serial.println(numberOfSensors);
  }

  // Sensor temperatures will be sent to Netio as JSON
  JsonDocument doc;
  JsonArray data = doc["temps"].to<JsonArray>();

  // Loop through each sensor, adding reported temperature to JSON
  for(int i=0;i<numberOfSensors; i++) {
    data.add(int(sensors.getTempCByIndex(i)));
  }

  // Send completed JSON string to Netio over rs232
  serializeJson(doc, netio);
  netio.write(0xd);

  serializeJson(doc, Serial);

  if (isDebugging) {
    Serial.println();
  }
  

  // Repeat every 4 seconds
  delay(4000);
}

