#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <fonts/FreeMono9pt7b.h>

// ── Display ──────────────────────────────────────────
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C
#define CHARACTER_WIDTH 5
#define MAX_SETTINGS 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ── Joystick ─────────────────────────────────────────
#define JOY_X   A0
#define JOY_Y   A1
#define JOY_BTN 2

void setup() {
  Serial.begin(115200);

  // Joystick button
  pinMode(JOY_BTN, INPUT_PULLUP);

  // Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Display not found — check wiring!");
    while (true);
  }

  // Startup screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(20, 28);
  display.print("building.");
  display.display();
  delay(1000);
}

//global variables

bool joy_left, joy_right, joy_up, joy_down;
int current_page=0;
int speed=50;
int interval;
bool btn;
int font_selected=1;
int dark_mode=1;
int highlight=0;

void highlight_word(String word){
  int16_t tx, ty;
  uint16_t tw, th;
  display.getTextBounds(word, 0, 15, &tx, &ty, &tw, &th);//take boundaries of the word
  if (font_selected==1) {
    display.fillRect(tx - 2, ty + 13, tw + 4, th + 4, WHITE);
  } else {
    display.fillRect(tx - 2, ty - 2, tw + 4, th + 4, WHITE);
  }
    //add white rectangle behind it
  display.setTextColor(BLACK);
  display.print(word); //print the text
  display.setTextColor(WHITE); //go back to default mode for text that appears aftwerwards
}
//function runned every frame
void loop() {
  // ── Read joystick ───────────────────────────────────
    int joy_x   = analogRead(JOY_X);         // 0 - 1023
    int joy_y   = analogRead(JOY_Y);         // 0 - 1023
    btn    = !digitalRead(JOY_BTN);     // true when button is pressed

  display.clearDisplay();
  display.setCursor(0, 0);
  joy_left=false, joy_right=false, joy_up=false, joy_down=false;
  if (joy_x<100){
    display.print((char)27);//left arrow symbol
    joy_left=true;
  } else if(600>joy_x && joy_x>400) {
    display.print((char)26);//right arrow symbol
    joy_right=true;
  } else if(joy_y<100) {
    display.print((char)24);//up arrow symbol
    joy_up=true;
    if (speed<100) speed++;
  } else if (600>joy_y && joy_y>400) {
    display.print((char)25);//down arrown symbol
    joy_down=true;
  } else if(btn==true){
    display.print((char)7);//button press => circle symbol
  } else {
    display.print(' ');
  }
  if (current_page==1){
    settings_page();
  } else {
    main_page();
  } 
  if (dark_mode==false){
    display.invertDisplay(true);
  } else {
    display.invertDisplay(false);
  }
    //update the display
  display.display();
  delay(50);
}

void settings_page(){
  static bool lastbtnstate=false;
  static uint32_t last_joy_left;
  static uint32_t last_joy_right;
  static int current_setting=0;
  static long last_time=0;
  
  struct MenuItem {
  String label;
  int* value;        // pointer to the setting value so that it changes it directly
  int minVal;
  int maxVal;
  };

  MenuItem menu[] = {
    { "highlight word", &highlight, 0, 1},
    { "dark mode", &dark_mode, 0, 1},
    { "font", &font_selected, 0, 1},
  };
  display.print("--settings page--");
      
  display.setCursor(0, 20);

  for (int i=0; i<MAX_SETTINGS; i++){
    if (i==current_setting){
      display.print('>'); //to show which one is selected
    }else {
      display.print(' ');
    }
    display.print(menu[i].label);
    for (int d=0; d<18-menu[i].label.length(); d++) display.print('.'); //print dots until value
    display.print(' ');
    display.print(*menu[i].value);
    display.print('\n');
  }

  if (joy_left && !last_joy_left){//joystick was just moved to the left
    //highlight? highlight= false: highlight=true;
  } 
  last_joy_left = joy_left;
  if (joy_right && !last_joy_right){//joystick was just moved to the right
    if (*menu[current_setting].value>=menu[current_setting].maxVal){
      *menu[current_setting].value=0;
    } else {
      *menu[current_setting].value=*menu[current_setting].value+1;
    } 
  } 
  last_joy_right = joy_right;

  if(joy_up) {
    if (millis()- last_time >= 300) {
      if (current_setting>0) {current_setting--;}
      last_time = millis();
    }
  } 
  if (joy_down) {
    if (millis()- last_time >= 300) {
      if (current_setting<MAX_SETTINGS-1) {current_setting++;}
      last_time = millis();
    }
  } 
  if(btn){//button pressed
    
  } else {
    //joystick centered
  }

    //tracks release of a button
  if (btn==false && lastbtnstate==true){
    current_page=0;
  }
  lastbtnstate= btn;

  
  display.setCursor(0, 50);
  display.print("press button to save"); 
}

void main_page(){

  uint32_t now = millis(); //current time in milliseconds
  static int current_word=0;
  static bool lastbtnstate=false;
  static uint32_t last_time=0;

  //split text into words
  String text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. end...";
  String words[100];
  int word_count = 0;


  while (text.length() > 0) {
      int spaceIndex = text.indexOf(' ');
      if (spaceIndex == -1) {
          words[word_count++] = text;    // last word
          break;
      }
      words[word_count++] = text.substring(0, spaceIndex);
      text = text.substring(spaceIndex + 1);
  }

  if(joy_left) {
    if (millis()- last_time >= interval) { //joystick is on the left for more than the intterval
      last_time = millis();
      if(current_word>0) current_word--;//go to next word until end of text
    }
  }
  if(joy_right) {
    static int i;
    if (millis()- last_time >= interval) { //joystick is on the right for more than the interval
      Serial.println("right");
      Serial.println(i);
      i++;
      last_time = millis();
      if(current_word<word_count-1) current_word++;//go to next word until end of text
    }
  } 
  if(joy_up) {
    if (speed<100) speed++;
  } 
  if (joy_down) {
    if (speed>0) speed--;
  } 
  if(btn){
    //button pressed
  } else {
    //joystick centered
  }
  display.print("--the pico book--");

  display.setCursor(0, 15);
  if(font_selected==1){
    display.setCursor(0, 25);
    display.setFont(&FreeMono9pt7b);
  }
  if (highlight) {
    highlight_word(words[current_word]);
  } else {
    display.print(words[current_word]);
  }
  display.setFont(0);

  //indicate joysticks input
  display.setCursor(0, 0);
  interval = map(speed, 0, 100, 500, 70); //map the speed variable into delay (slower speed => higher delay in milliseconds)



  //tracks release of a button
  if (btn==false && lastbtnstate==true){
    current_page=1;
  }
  lastbtnstate= btn;

  

  //print speed on the right bottom corner of the display
  display.setCursor(SCREEN_WIDTH-9*6, SCREEN_HEIGHT-10);
  display.print("speed:");
  char buffer[4];
  sprintf(buffer,"%3d", speed); //format speed to be aligned on the right of the screen
  display.print(buffer);  
}