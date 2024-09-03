//#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int led1 = 4;
int led2 = 5;
int led3 = 6;
int led4 = 7;
boolean startPage = true;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;
//SoftwareSerial dwinSerial(rxPin, txPin);

#define temp_variable_address 0x20
#define message_address 0x22
unsigned char Buffer[9];
unsigned char HexData[8] = {0x5A, 0xA5, 0x05, 0x82, 0x00, 0x00, 0x00, 0x00};

void setup() {

  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  startMillis = millis();
  dht.begin();

}

void Temp_Data_to_Display() {
  // Reading temperature and humidity data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  String dataToSend = String(temperature, 1) + " *C, " + String(humidity, 1) + " %";
  Serial.println(dataToSend);


  int t = temperature;
  HexData[4] = 0x20;
  HexData[6] = highByte(t);
  HexData[7] = lowByte(t);
  Serial.write(HexData, sizeof(HexData));
  //  if(!Serial.available()){
  //  Serial.println("Fail");
  //  return;
  //  }

  if (t < 30) {
    HexData[4] = message_address;
    HexData[7] = 0x00;  // Set the LOW icon byte to display

  } else if (t = 31) {
    HexData[4] = message_address;
    HexData[7] = 0x01;  // Set the NORMAL to display

  } else if ( t = 32) {
    HexData[4] = message_address;
    HexData[7] = 0x02;  // Set the HIGH to display
  } else if ( t = 33) {
    HexData[4] = message_address;
    HexData[7] = 0x03;  // Set the HIGH to display
  }

  Serial.write(HexData, 8);  // Send the data to the DWIN display

}
///********** Serial Data Read Function *************
void hal_rs232_communication_handler() {
  if (Serial.available()) {
    for (int i = 0 ; i <= 8; i++) {
      Buffer[i] = Serial.read();
      Serial.print(Buffer[i]);
      Serial.print(" ");
    }
    Serial.print("\t");
    Serial.print("BufferSize: ");
    Serial.print(sizeof(Buffer));
    Serial.println("\t");
  }
}
void Read_data_from_Display() {
//   hal_rs232_communication_handler();//Read Serial data to Buffer
  if (Buffer[0] == 0x5A) {
//    Serial.println("Yes ,reach it");
    switch (Buffer[4]) {
      case 48: //for light
        if (Buffer[8] == 0)
        {
          digitalWrite(led1, HIGH);
        } else
        {
          digitalWrite(led1, LOW);
        }
        break;
      case 49: //for light
        if (Buffer[8] == 0)
        {
          digitalWrite(led2, HIGH);
        } else
        {
          digitalWrite(led2, LOW);
        }
        break;
      case 50: //for light
        if (Buffer[8] == 0)
        {
          digitalWrite(led3, HIGH);
        } else
        {
          digitalWrite(led3, LOW);
        }
        break;
      case 51: //for light
        if (Buffer[8] == 1)
        {
          digitalWrite(led4, HIGH);
        } else
        {
          digitalWrite(led4, LOW);
        }
        break;
    }
  }


  //    Serial.print("\t");
  //    Serial.print("BufferSize: ");
  //    Serial.print(sizeof(Buffer));
  //    Serial.println("\t");

}


bool control_page = false;
void loop() {
//  Serial.println("Hello From Loop");
  hal_rs232_communication_handler();
  currentMillis = millis();
  if (currentMillis - startMillis >= period) {
    Temp_Data_to_Display();
    startMillis = currentMillis;
    Serial.print("Start milliseconds:");
    Serial.println(startMillis);
    Serial.print("Current milliseconds:");
    Serial.println(currentMillis);
  }
  
  Read_data_from_Display();

  //  if (Buffer[4] == 64) {
  //
  //  }
  //
  //  if(control_page) {
  //     Serial.println("Second page");
  //    Read_data_from_Display();
  //  }
  //  //  if(Buffer[4]== 65){
  //  //    startPage = true;
  //  //  }
  //  //  delay(3000);
}



////90 165 6 131 64 0 1 13 13
// if (Serial.available()) {
//    for (int i = 0 ; i <= 8; i++)
//    {
//      Buffer[i] = Serial.read();
//      Serial.print(Buffer[i]);
//      Serial.print(" ");
//      if(Buffer[8]==13){
//
//
//
//      Read_data_from_Display();
//  }
//  }
//
//
////  Serial.println("Yeah, I got u");
////  delay(1000);
//}
