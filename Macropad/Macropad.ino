#include <Adafruit_SSD1306.h>
#include <BleKeyboard.h>
#include <Images.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C


#define CLK 13
#define DT 4
#define BROWSER_PIN 14
#define YOUTUBE_PIN 27
#define GITHUB_PIN 26
#define NETFLIX_PIN 25
#define WHATSAPP_PIN 33
#define LMS_PIN 32


struct Button {
  const uint8_t pin;
  const char* name;
  const char* url;
  int currentState = HIGH;
  int lastState = HIGH;
  unsigned long lastDebounceTime = 0;
  const unsigned char** bitmapArray;
  const int noofframes;
};


Button buttons[] = {
  {BROWSER_PIN, "Chrome", nullptr, HIGH, HIGH, 0,nullptr,0},
  {YOUTUBE_PIN, "YouTube", "https://www.youtube.com", HIGH, HIGH, 0,youtube_logoallArray,15},
  {GITHUB_PIN, "GitHub", "https://github.com/", HIGH, HIGH, 0,github_logoallArray,1},
  {NETFLIX_PIN, "Netflix", "8", HIGH, HIGH, 0,netflix_logoallArray,13},
  {WHATSAPP_PIN, "Whatsapp", "3", HIGH, HIGH, 0,Whatsapp_LogoallArray,1},
  {LMS_PIN, "LMS", "https://lms.eng.sjp.ac.lk/", HIGH, HIGH, 0,nullptr,0}
};


const unsigned long DEBOUNCE_DELAY = 50; 
const uint8_t BUTTON_COUNT = 6;

Adafruit_SSD1306 display (SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);



static uint8_t state = 0;           

BleKeyboard bleKeyboard;

void setup() {

  Serial.begin(115200);
  bleKeyboard.begin();

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(2,OUTPUT);
  
 for (uint8_t i = 0;i<BUTTON_COUNT;i++){
  pinMode(buttons[i].pin, INPUT_PULLUP);
 }

 if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }

}

void loop() {

  if(bleKeyboard.isConnected()) {
    readEncoder();  // Volume Control
    
    checkButtons();
    digitalWrite(2, 1);


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


void checkButtons(){

  for (uint8_t i = 0;i<BUTTON_COUNT;i++){
    if(Debounce(&buttons[i])){

      if(i==0){
        bleKeyboard.write(KEY_MEDIA_WWW_HOME);
      }
      else if(buttons[i].name == "Netflix" || buttons[i].name == "Whatsapp"){
        Open_App(buttons[i].url);
        draw_Bitmap(buttons[i].bitmapArray,buttons[i].noofframes);

        
      }
      else{
        Open_Website(buttons[i].url);
        //draw_Bitmap(buttons[i].bitmapArray,buttons[i].noofframes);
        draw_Bitmap(buttons[i].bitmapArray,buttons[i].noofframes);
      }


      return;
    }
  }
}


bool Debounce(Button* button) {
  int reading = digitalRead(button->pin);
  

  if (reading != button->lastState) {
    button->lastDebounceTime = millis();  
  }
  

  if ((millis() - button->lastDebounceTime) > DEBOUNCE_DELAY) {
    
    if (reading != button->currentState) {
      button->currentState = reading;
      
      
      if (button->currentState == LOW) {
        return true;
      }
    }
  }
  
  button->lastState = reading;
  return false;
}

void Open_Website(const char* url) {

  bleKeyboard.press(KEY_LEFT_GUI);
  bleKeyboard.print("r");
  delay(100);
  bleKeyboard.releaseAll();
  delay(200);
  
  for(int i = 0; i < strlen(url); i++) {
    bleKeyboard.print(url[i]);
    delay(10);  
  }
  
  delay(700);
  bleKeyboard.press(KEY_RETURN);
  delay(200);
  bleKeyboard.releaseAll();
}

void Open_App(const char* url){

  bleKeyboard.press(KEY_LEFT_GUI);
  bleKeyboard.print(url);
  bleKeyboard.releaseAll();
}

void draw_Bitmap(const unsigned char** bitmapArray,int frameCount){

 for (int i =0;i< frameCount; i++){

  if (frameCount == 1){
    display.clearDisplay();
    display.drawBitmap(0,0,bitmapArray[i],128,64,1);
    display.display();
    delay(2000);
    break;
  }
  display.clearDisplay();
  display.drawBitmap(0,0,bitmapArray[i],128,64,1);
  display.display();
  delay(50);
 }

 display.clearDisplay();
 display.display();
}