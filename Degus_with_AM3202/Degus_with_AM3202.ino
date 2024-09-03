#include "DHT.h"

#define DHTPIN 2     // Pin where the data pin of the DHT22 is connected
#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
#define temp 0x20
unsigned char Buffer[9];
unsigned char address[8]= {0x5A,0xA5,0x05,0x82,temp,0x00,0x00,0x00}; 

void setup() {
  Serial.begin(115200); 
  dht.begin();
}

void loop() {
  // Reading temperature and humidity data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int t = temperature;
  address[6] = highByte(t);
  address[7] = lowByte(t);
  Serial.write(address,8);
  if(!Serial.available()){
  Serial.println("Fail");
  return;
  }
  String dataToSend = String(temperature, 1) + " *C, " + String(humidity, 1) + " %";
  Serial.println(dataToSend);
  
  delay(1000);
}
