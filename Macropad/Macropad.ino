#include <BleKeyboard.h>


#define CLK_PIN 13
#define DT_PIN 4

#define DIRECTION_CW 0
#define DIRECTION_CCW 1

int counter = 0;
int direction  = DIRECTION_CW;
int CLK_state;
int prev_CLK_state;


BleKeyboard bleKeyboard;

bool buttonStateYT = false;
bool buttonStateGT = false;


void setup() {
  Serial.begin(115200);
  
 
  bleKeyboard.begin();
 
  pinMode(5,INPUT_PULLUP); // OPen YT
  pinMode(18,INPUT_PULLUP); // Open Github
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN,INPUT_PULLUP);
  
  prev_CLK_state = digitalRead(CLK_PIN);

}

void loop() {

// Volume Control



if(bleKeyboard.isConnected()) {


  CLK_state = digitalRead(CLK_PIN);


  if (CLK_state != prev_CLK_state && CLK_state == HIGH){
    if (digitalRead(DT_PIN) == HIGH){

      delay(50);

      if (digitalRead(DT_PIN) == HIGH){
      counter--;
      direction = DIRECTION_CCW; 
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      // Serial.println("Volume Down");

      }

    }
    if (digitalRead(DT_PIN) == LOW){

      delay(50);
      
      if (digitalRead(DT_PIN) == LOW){

      
      counter++;
      direction = DIRECTION_CW; 
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      // Serial.println("Volume Up");

      }

    }

  }

Serial.println(counter);
prev_CLK_state = CLK_state;

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