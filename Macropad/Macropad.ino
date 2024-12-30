
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
bool buttonStateYT = false;
bool buttonStateGT = false;

void setup() {
  Serial.begin(115200);
  
 
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
   
  

  
// Open Youtube
if (digitalRead(5) == LOW){
  delay(50);

if (digitalRead(5) == LOW){
  buttonStateYT = !buttonStateYT;

if (buttonStateYT){

bleKeyboard.press(KEY_LEFT_GUI);
bleKeyboard.print("r");
bleKeyboard.releaseAll();

delay(500);
bleKeyboard.print("www.youtube.com");

bleKeyboard.press(KEY_RETURN);
bleKeyboard.releaseAll();
Serial.println("Youtube");
}

}

}

if(digitalRead(18) == LOW){
  delay(50);

if (digitalRead(18) == LOW){
  buttonStateGT = !buttonStateGT;

if (buttonStateGT){

bleKeyboard.press(KEY_LEFT_GUI);
bleKeyboard.print("r");
bleKeyboard.releaseAll();

delay(500);
bleKeyboard.print("www.github.com");

bleKeyboard.press(KEY_RETURN);

bleKeyboard.releaseAll();
Serial.println("Github");

}

}

}


  }

 else{
    Serial.println("NOT CONNECTED");
    delay(1000);
  }





}