#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ── Display ──────────────────────────────────────────
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C
#define CHARACTER_WIDTH 5

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


bool highlight=false;
bool joy_left, joy_right, joy_up, joy_down;
int current_page=0;
int speed=50;
void loop() {

  // ── Read joystick ───────────────────────────────────
    int joy_x   = analogRead(JOY_X);         // 0 - 1023
    int joy_y   = analogRead(JOY_Y);         // 0 - 1023
    bool btn    = !digitalRead(JOY_BTN);     // true when button is pressed

  display.clearDisplay();
  display.setCursor(0, 0);
  joy_left=false, joy_right=false, joy_up=false, joy_down=false;
  if (joy_x==0){
    display.print((char)27);//left arrow symbol
    joy_left=true;
  } else if(600>joy_x && joy_x>400) {
    display.print((char)26);//right arrow symbol
    joy_right=true;
  } else if(joy_y==0) {
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
    settings_page(joy_x, joy_y, btn);
  } else {
    main_page(joy_x, joy_y, btn);
  } 
    //update the display
  display.display();
  delay(10);
}

void settings_page(int joy_x, int joy_y, bool btn){
  static bool lastbtnstate=false;

  /*   if (joy_left){
    
  } 
  if(joy_right) {
    
  } 
  if(joy_up) {
    
  } 
  if (joy_down) {
    
  } 
  if(btn){//button pressed
    
  } else {
    //joystick centered
  } */

    //tracks release of a button
  if (btn==false && lastbtnstate==true){
    current_page=0;
  }
  lastbtnstate= btn;
  display.print("--settings page--");
      
  display.setCursor(0, 20);
  display.print("highlight word: ");highlight? display.print("true\n"):display.print("false\n");
  display.setCursor(0, 50);
  display.print("press button to save"); 
}

void main_page(int joy_x, int joy_y, bool btn){
  static int highlighted_word=0;
  static bool lastbtnstate=false;

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

  if (joy_left){
    if(highlighted_word>0) highlighted_word--; //go one word back
  } 
  if(joy_right) {
    if(highlighted_word<word_count-1) highlighted_word++; //go to next word until end of text
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



  //indicate joysticks input
  display.setCursor(0, 0);
  int ms_delay = map(speed, 0, 100, 200, 30); //map the speed variable into delay (slower speed => higher delay in milliseconds)



  //tracks release of a button
  if (btn==false && lastbtnstate==true){
    current_page=1;
  }
  lastbtnstate= btn;

  //highlight word
  int16_t tx, ty;
  uint16_t tw, th;
  display.getTextBounds(words[highlighted_word], 0, 15, &tx, &ty, &tw, &th);
  if (highlight==true){
    display.fillRect(tx - 2, ty - 2, tw + 4, th + 4, WHITE);
    display.setTextColor(BLACK);
  }
  display.setCursor(0, 15);
  display.print(words[highlighted_word]);
  display.setTextColor(WHITE);

  //print speed on the right bottom corner of the display
  display.setCursor(SCREEN_WIDTH-9*6, SCREEN_HEIGHT-10);
  display.print("speed:");
  char buffer[4];
  sprintf(buffer,"%3d", speed); //format speed to be aligned on the right of the screen
  display.print(buffer);  
}