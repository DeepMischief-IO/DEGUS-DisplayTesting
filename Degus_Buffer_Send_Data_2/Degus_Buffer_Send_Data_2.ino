#define temp 0x10
unsigned char Buffer[9];
unsigned char address[8]= {0x5A,0xA5,0x05,0x82,temp,0x00,0x00,0x00}; 
void setup() {
  Serial.begin(115200);
  
}

void loop() {
  address[6]=highByte('A');
   address[7]=lowByte('A');
  
  Serial.write(address,sizeof(address));
  if(!Serial.available()){
  Serial.println("Fail");
  return;
  }
  
delay(1000);
}
