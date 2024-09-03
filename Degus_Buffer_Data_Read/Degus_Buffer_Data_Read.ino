unsigned char Buffer[9];
int red = 13;
int green = 5;
int blue = 6;
int servo = 3;
int relay = 2;
 
void setup()
{
  Serial.begin(115200);
 
  pinMode(servo, OUTPUT);
  digitalWrite(servo, LOW);
  pinMode(red, OUTPUT);
  digitalWrite(red, LOW);
  pinMode(green, OUTPUT);
  digitalWrite(green, LOW);
  pinMode(blue, OUTPUT);
  digitalWrite(blue, LOW);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}
 
void loop()
{

  if (Serial.available())
  {
    hal_rs232_communication_handler();//to print the buffer array and values
//    for (int i = 0; i <= 8; i++) //this loop will store whole frame in buffer array.
//    {
//      Buffer[i] = Serial.read();
//    }
// 
    if (Buffer[0] == 90)
    {
      switch (Buffer[8])
      {
        case 0x51:   //for servo
          Serial.println(Buffer[8]);
          analogWrite(servo, Buffer[8]);
          break;
 
        case 0:   //for red
          Serial.println(Buffer[8]);
          digitalWrite(red, Buffer[8]);
          break;
 
        case 1:   //for green
          Serial.println(Buffer[8]);
          digitalWrite(red, Buffer[8]);
          break;
 
 
        case 0x54:   //for blue
          Serial.println(Buffer[8]);
          analogWrite(blue, Buffer[8]);
          break;
 
        case 0x55:  //for relay
          if (Buffer[8] == 1)
          { digitalWrite(relay, HIGH);
            Serial.println("relay on");
          }
          else
          { digitalWrite(relay, LOW);
            Serial.println("relay off");
          }
          break;
 
 
        default:
          Serial.println("Nothing");
          break;
      }
    }
  }
  delay(10);
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
}}
