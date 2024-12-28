#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  pinMode(13,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);

}

void loop() {
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

  
}