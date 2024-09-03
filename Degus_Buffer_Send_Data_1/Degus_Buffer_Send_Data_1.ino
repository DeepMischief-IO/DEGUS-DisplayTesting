  unsigned char Buffer[9];
int led = 13;
int relay1 = 5;
int relay2 =6;
byte onLed[]= {0x5A,0xA5,0x05,0x82,0x55,0x00,0x00,0x00}; 
byte offLed[]= {0x5A,0xA5,0x05,0x82,0x55,0x00,0x00};
void setup() {
 Serial.begin(115200);
 pinMode(led,OUTPUT);
 pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
 digitalWrite(led,LOW);
 Serial.println("Begin Serial ");
 

}
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
    Serial.print("\t");
}
}
void loop() {
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
    
    if(Buffer[0] == 0X5A){
        switch(Buffer[5]){        /////
            case 0:
               if(Buffer[8]==1){
                digitalWrite(relay1,HIGH);
                break;
               }else{

               digitalWrite(relay1,LOW);
               break;
               }
        case 1:
               if(Buffer[8]==1){
                digitalWrite(relay2,HIGH);
                break;
               }else{

               digitalWrite(relay2,LOW);
               break;
               }
               
        default:
                Serial.println("No Data");
                break;
      }
    }
  
  
}
