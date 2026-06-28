#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <fonts/FreeMono9pt7b.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include <avr/pgmspace.h>
#include "book.h"
using namespace Adafruit_LittleFS_Namespace;

// Display
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C
#define CHARACTER_WIDTH 5
#define MAX_SETTINGS 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick
#define JOY_X   A0
#define JOY_Y   A2
#define JOY_BTN 1

// ALL GLOBAL VARIABLES

//word and character counting
int BOOK_SIZE_WORDS = 0;
int BOOK_SIZE_CHARACTERS = 0;

//scrolling feature
int word_length = 0;

//joystick
bool joy_left, joy_right, joy_up, joy_down, btn;

int interval;

bool check = true;

struct SavedData {
  int font_selected = 0;
  int dark_mode = 1;
  int highlight = 0;
  int current_word = 0;
  int current_page = 0;
  int32_t current_character = 0;
  int speed = 60;
} data;

File file(InternalFS);

void saveData() {
  InternalFS.remove("data.bin");
  file.open("data.bin", FILE_O_WRITE);
  if (file) {
    file.write((uint8_t*)&data, sizeof(data));  // save struct as bytes
    file.close();
  }
}

void reset(){
  data.current_character=0;
  data.current_word=0;
}

//function that is called once at the beginning of the code
void setup() {
  Serial.begin(115200); 
  InternalFS.begin();
  Serial.println("Setup Started");

  file.open("data.bin", FILE_O_READ);
  if (file) {
    // file exists — load it
    file.read((uint8_t*)&data, sizeof(data));
    file.close();
    data.current_page = 0;
  } else {
    saveData();
  }

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
  display.print("building...");
  display.display();
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.println("Setup complete");

  // Counting the total number of characters
  int count_character = 0; //variable only used for counting
  while (pgm_read_byte(&BOOK[count_character])!= '\0') {
    count_character ++;
  } 
  BOOK_SIZE_CHARACTERS = count_character;

  // Counting the total number of words
  count_character = 0; //reset of the counting variable
  while (getWord(count_character)!= "") {
    BOOK_SIZE_WORDS ++;
    count_character += word_length;
  }
  BOOK_SIZE_WORDS--; //since word count is counting the null terminator as a word

  //if a new text gets upload with less words than the previous one and the cursor beeing at a place that doesen't exist in the new text, the reset function is needed to not get stuck
  if (data.current_word > BOOK_SIZE_WORDS) {
    reset();
  }
}

//function running every frame
void loop() {
  //Read joystick
    int joy_x   = analogRead(JOY_X);         // 0 - 1023
    int joy_y   = analogRead(JOY_Y);         // 0 - 1023
    btn    = !digitalRead(JOY_BTN);     // true when button is pressed
  display.clearDisplay();
  display.setCursor(0, 0);
  joy_left=false, joy_right=false, joy_up=false, joy_down=false;
  if (joy_x>650){
    display.print((char)27);//left arrow symbol
    joy_left=true;
  } else if(200>joy_x) {
    display.print((char)26);//right arrow symbol
    joy_right=true;
  } else if(joy_y>650) {
    display.print((char)24);//up arrow symbol
    joy_up=true;
  } else if (joy_y<200) {
    display.print((char)25);//down arrown symbol
    joy_down=true;
  } else if(btn==true){
    display.print((char)7);//button press => circle symbol
  } else {
    display.print(' ');
  }
  if (data.current_page==1){
    settings_page();
  } else {
    main_page();
  } 
  if (data.dark_mode==false){
    display.invertDisplay(true);
  } else {
    display.invertDisplay(false);
  }
    //update the display
  display.display();
  delay(50);
}

//when called, it showes the settings page
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
    { "highlight word", &data.highlight, 0, 1},
    { "dark mode", &data.dark_mode, 0, 1},
    { "font", &data.font_selected, 0, 1},
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
    reset();
    display.clearDisplay();
    printCentered("reset the screen");
    display.display();
    delay(1000);
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
    data.current_page=0;
    display.clearDisplay();
    printCentered("saved!");
    display.display();
    saveData();
  }
  lastbtnstate= btn;
  
  display.setCursor(0, 50);
  display.print("press button to save"); 
}

//when called its showing the main page where you can read the text
void main_page(){
  uint32_t now = millis(); //current time in milliseconds
  static bool lastbtnstate=false;
  static uint32_t last_time=0;

  if(joy_left) {
    if (millis()- last_time >= interval) { //joystick is on the left for more than the interval
      last_time = millis();
      if(data.current_word > 0) {
        data.current_word--;//update counter
        data.current_character -= getPreviousWordLength(data.current_character);//go to the character index of the previous word
        Serial.println("left");
      } else {
        //data.current_character=0;
      }
    }
  }
  if(joy_right) {
    static int i;
    if (millis()- last_time >= interval) { //joystick is on the right for more than the interval
      i++;
      last_time = millis();
      if(data.current_word<BOOK_SIZE_WORDS) {
        data.current_word++;//update word counter
        data.current_character += word_length;
        }//go to next word until end of text
    }
  } 
  if(joy_up) {
    if (data.speed<100) data.speed++;
  } 
  if (joy_down) {
    if (data.speed>0) data.speed--;
  } 
  if(btn){
    //button pressed
  }

  //tracks release of a button
  if (btn==false && lastbtnstate==true){
    data.current_page=1;
    //saveData();
  }
  lastbtnstate= btn;

  if (data.speed == 100 && check == true) {
    char text[] = "BEAST MODE ACTIVATED";
    char buffer[21] = "";
    for (int i = 0; i < 21; i++) {
      display.clearDisplay();
      for (int j = 0; j < i; j++) {
        buffer[j] = text[j];
        }
      String arduinoString = String(buffer);
      printCentered(arduinoString);
      display.display();
      delay (100);
    }
    check = false;
  } else if (data.speed == 100 && check == false) {
      display.setCursor(SCREEN_WIDTH - 9, 0);
      display.print("X");
    } else if (data.speed != 100) {
        check = true;
     }
  display.print(" --the pico book--");

    display.setCursor(1, 15);
    if(data.font_selected==1){
    display.setCursor(0, 25);
    display.setFont(&FreeMono9pt7b);
  }
  if (data.highlight) {
    highlight_word(getWord(data.current_character));
  } else {
    display.print(getWord(data.current_character));
  }
  display.setFont(0);

  //display progression: current word over total
  display.setCursor(0, SCREEN_HEIGHT-10);
  display.print(data.current_word+1); //+1 so that it starts at one and not zero
  display.print("/");
  display.print(BOOK_SIZE_WORDS+1);

  //indicate joysticks input
  display.setCursor(0, 0);
  interval = map(data.speed, 0, 100, 500, 70); //map the speed variable into delay (slower speed => higher delay in milliseconds)

  //print speed on the right bottom corner of the display
  display.setCursor(SCREEN_WIDTH-9*6, SCREEN_HEIGHT-10);
  display.print("speed:");
  char buffer[4];
  sprintf(buffer,"%3d", data.speed); //format speed to be aligned on the right of the screen
  display.print(buffer);
}

void printCentered (String text) {
  int16_t tx, ty;
  uint16_t tw, th;
  display.getTextBounds(text, 0, 0, &tx, &ty, &tw, &th);
  display.setCursor((SCREEN_WIDTH)/2 - (tw/2), (SCREEN_HEIGHT/2) - (th/2));
  display.print(text);
}

int getPreviousWordLength(unsigned long character_index) {
    int total = 0;
    // skip whitespace between current position and end of previous word
    while (character_index > 0 && isSpace(pgm_read_byte(&BOOK[character_index - 1]))) {
        character_index--; total++;
    }
    // skip the previous word itself
    while (character_index > 0 && !isSpace(pgm_read_byte(&BOOK[character_index - 1]))) {
        character_index--; total++;
    }
    return total;
}
String getWord(unsigned long character_index) {
    String word = "";
    word_length = 0;
    int leading = 0;

    while (character_index < BOOK_SIZE_CHARACTERS) {
        char c = pgm_read_byte(&BOOK[character_index]);
        if (c != ' ' && c != '\n' && c != '\r') break;
        character_index++; leading++;
    }
    while (character_index < BOOK_SIZE_CHARACTERS) {
        char c = pgm_read_byte(&BOOK[character_index]);
        if (c == ' ' || c == '\n' || c == '\r') break;
        word += c; character_index++; word_length++;
    }
    word_length += leading + 1;  // include skipped whitespace + one trailing separator
    return word;
}
void highlight_word(String word){
  int16_t tx, ty;
  uint16_t tw, th;
  display.getTextBounds(word, 0, 15, &tx, &ty, &tw, &th);//take boundaries of the word
  if (data.font_selected==1) {
    display.fillRect(tx - 2, ty + 13, tw + 4, th + 4, WHITE);//change the box location if font 1 is selected
  } else {
    display.fillRect(tx - 2, ty - 2, tw + 4, th + 4, WHITE);
  }
    //add white rectangle behind it
  display.setTextColor(BLACK);
  display.print(word); //print the text
  display.setTextColor(WHITE); //go back to default mode for text that appears aftwerwards
}