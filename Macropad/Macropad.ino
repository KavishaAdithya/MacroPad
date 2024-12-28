
#include <BluetoothSerial.h>

#include <BleKeyboard.h>

BluetoothSerial SerialBT;
BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 Keyboard");
 
  bleKeyboard.begin();
  pinMode(13,INPUT_PULLUP); // Volume down
  pinMode(4,INPUT_PULLUP); // Volume UP
  pinMode(5,INPUT_PULLUP); // OPen YT
  pinMode(18,INPUT_PULLUP); // Open Github

}

void loop() {
// Volume Control

  if(bleKeyboard.isConnected()) {

 if(digitalRead(13) == LOW){

      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
          Serial.println("Volume Down");
          delay(150);
  
    }


    if(digitalRead(4) == LOW){

      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
          Serial.println("Volume Up");
          delay(150);     
    }
   
  }

  else{
    Serial.println("NOT CONNECTED");
    delay(1000);
  }

// Open Youtube/ FaceBook 

if (digitalRead(5) == LOW){

Serial.println("Youtube");
delay(500);

}

if(digitalRead(18) == LOW){

Serial.println("Github");
delay(500);

}







}