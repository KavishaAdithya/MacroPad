#include <BleKeyboard.h>

#define CLK 13
#define DT 4
#define Browser_pin 14
#define Youtube 27
#define Github 26

int16_t inputDelta = 0;   

int button_state = HIGH;
int lastButtonState = HIGH;          // Counts up or down depending which way the encoder is turned
static uint8_t state = 0;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;


BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
 
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT,INPUT_PULLUP);
  pinMode(Browser_pin,INPUT_PULLUP);
  pinMode(Youtube,INPUT_PULLUP);
  pinMode(Github, INPUT_PULLUP);

}


void loop() {
  
 if(bleKeyboard.isConnected()) {

  readEncoder();    // Volume Control 

  if (digitalRead(Browser_pin) == 0){
    delay(100);
    if (digitalRead(Browser_pin) == 0){
    bleKeyboard.write(KEY_MEDIA_WWW_HOME);
    Serial.write("Chrome");
    }  
  }

  // if(debounce_delay(Youtube)){

  //   Open_Website("https://www.youtube.com");

  // }

  if(debounce_delay(Github)){

    Open_Website("https://github.com/");

  }


}

 else{
    Serial.println("NOT CONNECTED");
    delay(1000);
  }

}


void readEncoder() {
    
    bool CLKstate = digitalRead(CLK);
    bool DTstate = digitalRead(DT);

    switch (state) {
        case 0:                         // Idle state, encoder not turning
            if (!CLKstate){             // Turn clockwise and CLK goes low first
                state = 1;
            } else if (!DTstate) {      // Turn anticlockwise and DT goes low first
                state = 4;
            }
            break;
        // Clockwise rotation
        case 1:                     
            if (!DTstate) {             // Continue clockwise and DT will go low after CLK
                state = 2;
            } 
            break;
        case 2:
            if (CLKstate) {             // Turn further and CLK will go high first
                state = 3;
            }
            break;
        case 3:
            if (CLKstate && DTstate) {  // Both CLK and DT now high as the encoder completes one step clockwise
                state = 0;
                bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
                
            }
            break;
        // Anticlockwise rotation
        case 4:                         // As for clockwise but with CLK and DT reversed
            if (!CLKstate) {
                state = 5;
            }
            break;
        case 5:
            if (DTstate) {
                state = 6;
            }
            break;
        case 6:
            if (CLKstate && DTstate) {
                state = 0;
                bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
            }
            break; 
    }

  
}


bool debounce_delay(int button_pin){


  int reading = digitalRead(button_pin);


  if (reading != lastButtonState){
  lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime)>debounceDelay){

  if(reading!=button_state){
    button_state = reading;

    if(button_state == LOW){
      lastButtonState = reading;
      return true;
    }

   
    }
  }

  lastButtonState = reading;
  return false;
}


void Open_Website (String url){

  bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("r");
    delay(100);
    bleKeyboard.releaseAll();
    delay(200);

    for(int i = 0; i < url.length(); i++) {
      bleKeyboard.print(url[i]);
      delay(10); // Small delay between characters
    }
    delay(2000);
    bleKeyboard.press(KEY_RETURN);
    delay(300);
    bleKeyboard.releaseAll();


}


