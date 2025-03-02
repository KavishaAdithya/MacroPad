#include <BleKeyboard.h>

#define CLK 13
#define DT 4
#define Browser_pin 14
#define Youtube 27
#define Github 26
#define Netflix 25
#define Gitbash 33
#define LMS 32


struct ButtonState {
  int currentState = HIGH;
  int lastState = HIGH;
  unsigned long lastDebounceTime = 0;
};


ButtonState browserButton;
ButtonState youtubeButton;
ButtonState githubButton;
ButtonState netflixButton;
ButtonState gitBashButton;
ButtonState LMSButton;

unsigned long debounceDelay = 50;   

int16_t inputDelta = 0;
static uint8_t state = 0;           

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(Browser_pin, INPUT_PULLUP);
  pinMode(Youtube, INPUT_PULLUP);
  pinMode(Github, INPUT_PULLUP);
  pinMode(Netflix,INPUT_PULLUP);
  pinMode(Gitbash, INPUT_PULLUP);
  pinMode(LMS,INPUT_PULLUP);
}

void loop() {
  if(bleKeyboard.isConnected()) {
    readEncoder();  // Volume Control
    
    // Browser button
    if(debounce_delay(Browser_pin, &browserButton)) {
      bleKeyboard.write(KEY_MEDIA_WWW_HOME);
      Serial.println("Chrome");
    }
    
    // YouTube button
    else if(debounce_delay(Youtube, &youtubeButton)) {
      Open_Website("https://www.youtube.com");
    }
    
    // GitHub button
    else if(debounce_delay(Github, &githubButton)) {
      Open_Website("https://github.com/");
    }

    else if(debounce_delay(Netflix,&netflixButton)){
      Open_Website("");
    }

    else if(debounce_delay(Gitbash,&gitBashButton)){
      Open_Website("");
    }

    else if(debounce_delay(LMS,&LMSButton)){
      Open_Website("https://lms.eng.sjp.ac.lk/");
    }


  }
  else {
    Serial.println("NOT CONNECTED");
    delay(1000);
  }
}

void readEncoder() {
  bool CLKstate = digitalRead(CLK);
  bool DTstate = digitalRead(DT);
  
  switch (state) {
    case 0:                         
      if (!CLKstate) {              
        state = 1;
      } else if (!DTstate) {        
        state = 4;
      }
      break;
      
    // Clockwise rotation
    case 1:                                  
      if (!DTstate) {               
        state = 2;
      }
      break;
      
    case 2:
      if (CLKstate) {               
        state = 3;
      }
      break;
      
    case 3:
      if (CLKstate && DTstate) {    
        state = 0;
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      }
      break;
      
    // Anticlockwise rotation
    case 4:                         
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


bool debounce_delay(int button_pin, ButtonState* button) {
  int reading = digitalRead(button_pin);
  

  if (reading != button->lastState) {
    button->lastDebounceTime = millis();  
  }
  

  if ((millis() - button->lastDebounceTime) > debounceDelay) {
    
    if (reading != button->currentState) {
      button->currentState = reading;
      
      
      if (button->currentState == LOW) {
        button->lastState = reading;
        return true;
      }
    }
  }
  
  button->lastState = reading;
  return false;
}

void Open_Website(String url) {
  bleKeyboard.press(KEY_LEFT_GUI);
  bleKeyboard.print("r");
  delay(100);
  bleKeyboard.releaseAll();
  delay(200);
  
  for(int i = 0; i < url.length(); i++) {
    bleKeyboard.print(url[i]);
    delay(10);  
  }
  
  delay(1000);
  bleKeyboard.press(KEY_RETURN);
  delay(300);
  bleKeyboard.releaseAll();
}