#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define RX_PIN 10     // RX pin for SoftwareSerial
#define TX_PIN 11     // TX pin for SoftwareSerial
#define ICON_ADDR 0x1000 // Starting VP address for icons
unsigned char address[8]= {0x5A,0xA5,0x05,0x82,0x20,0x00,0x00,0x00};
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial displaySerial(RX_PIN, TX_PIN);

struct Icon {
    float minTemp;
    float maxTemp;
    uint16_t iconAddress;
};

Icon icons[] = {
    { -10, 0, 0x01 },   // Icon for -10°C to 0°C
    { 0, 10, 0x02 },    // Icon for 0°C to 10°C
    { 10, 20, 0x03 },   // Icon for 10°C to 20°C
    { 20, 28, 0x00 },   // Icon for 20°C to 30°C
    { 29, 40, 0x01 }    // Icon for 30°C to 40°C
};

void setup() {
    Serial.begin(9600);        // For debugging
    displaySerial.begin(9600); // For communication with the display
    dht.begin();
}

float readTemperature() {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Failed to read from DHT sensor!");
        return -1;
    } else {
      Serial.print("Temperature is:");
      Serial.println(temp);
     
      return temp;
    }
}

void sendCommand(uint16_t address, uint16_t value) {
    uint8_t command[] = {0x5A, 0xA5, 0x05, 0x82, 
                         (address >> 8) & 0xFF, address & 0xFF, 
                         (value >> 8) & 0xFF, value & 0xFF};

    displaySerial.write(command, sizeof(command));
}

void updateIcon(float temperature) {
    for (int i = 0; i < sizeof(icons)/sizeof(icons[0]); i++) {
        if (temperature >= icons[i].minTemp && temperature < icons[i].maxTemp) {
            sendCommand(ICON_ADDR, icons[i].iconAddress);
            break;
        }
    }
}

void loop() {
  
    float temperature = readTemperature();
    if (temperature != -1) {
        updateIcon(temperature);
    }
    delay(2000); // Update every 2 seconds
}
