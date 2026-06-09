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
  display.print("Ready to build!");
  display.display();
  delay(1000);
}
int speed=0;
int highlighted_word=0;
void loop() {
  // ── Read joystick ───────────────────────────────────
  int joy_x   = analogRead(JOY_X);         // 0 - 1023
  int joy_y   = analogRead(JOY_Y);         // 0 - 1023
  bool btn    = !digitalRead(JOY_BTN);     // true when pressed

  // ── Draw ────────────────────────────────────────────
  display.clearDisplay();
  display.setCursor(0, 20);
  //split text into words
  String text = "Lorem ipsum dolor sitet amet, consectetur adipiscing elit.";
  String words[20];
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

  //indicate joysticks input
  display.setCursor(0, 0);
  
  if (joy_x==0){
    display.print((char)27);//left arrow symbol
    if(highlighted_word>0) highlighted_word--; //go one word back
  } else if(600>joy_x && joy_x>500) {
    display.print((char)26);//right arrow symbol
    if(highlighted_word<word_count) highlighted_word++; //go to next word
  } else if(joy_y==0) {
    display.print((char)24);//up arrow symbol
    if (speed<100) speed++;
  } else if (600>joy_y && joy_y>400) {
    display.print((char)25);//down arrown symbol
    if (speed>0) speed--;
  } else if(btn==true){
    display.print((char)7);//button press => circle symbol
  }
  display.setCursor(10,0);
  display.print("--the pico book--");

  //highlight word
  int16_t tx, ty;
  uint16_t tw, th;
  display.getTextBounds(words[highlighted_word], 0, 15, &tx, &ty, &tw, &th);
  display.fillRect(tx - 2, ty - 2, tw + 4, th + 4, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(0, 15);
  display.print(words[highlighted_word]);
  display.setTextColor(WHITE);

  

  //print speed on the right bottom corner of the display
  display.setCursor(SCREEN_WIDTH-9*6, SCREEN_HEIGHT-10);
  display.print("speed:");
  char buffer[4];
  sprintf(buffer,"%3d", speed); //format speed to be aligned on the right of the screen
  display.print(buffer);

  // ── scrolling feature ────────────────────────────

  int ms_delay = map(speed, 0, 100, 200, 30); //map the speed variable into delay (slower speed => higher delay in milliseconds)
  //update the display
  display.display();
  delay(ms_delay);
}