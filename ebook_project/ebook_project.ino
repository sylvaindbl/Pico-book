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
void loop() {
  // ── Read joystick ───────────────────────────────────
  int joy_x   = analogRead(JOY_X);         // 0 - 1023
  int joy_y   = analogRead(JOY_Y);         // 0 - 1023
  bool btn    = !digitalRead(JOY_BTN);     // true when pressed

  // ── Draw ────────────────────────────────────────────
  display.clearDisplay();

  //indicate joysticks input
  display.setCursor(0, 0);
  if (joy_x==0){
    display.print((char)27);//left arrow symbol
  } else if(600>joy_x && joy_x>500) {
    display.print((char)26);//right arrow symbol
  } else if(joy_y==0) {
    display.print((char)24);//up arrow symbol
    if (speed<100) speed++;
  } else if (600>joy_y && joy_y>400) {
    display.print((char)25);//down arrown symbol
    if (speed>0) speed--;
  } else if(btn==true){
    display.print((char)7);//button press => circle symbol
  }

  //title
  display.setCursor(10,0);
  display.print("--the pico book--");

  //print speed on the right bottom corner of the display
  display.setFont();
  display.setCursor(SCREEN_WIDTH-9*6, SCREEN_HEIGHT-10);
  display.print("speed:");
  char buffer[4];
  sprintf(buffer,"%3d", speed); //format speed to be aligned on the right of the screen
  display.print(buffer);

  //printing the text
  int y = 0; //y coordinate of the display
  int x = 0; //x coordinate of the display
  const char* lines[] = {
    "Lorem ipsum", "dolor sit amet", "consetetur sadipcing", "elitr.",
  };
  int lineCount = 4;
  display.setFont(&FreeMono9pt7b);
  y = 24;
  display.setCursor(0, y);
  /* for (int i = 0; i < lineCount; i++) {
    display.print(lines[i]);
    display.setCursor(0, y += 12);
  } */
  display.print("test");
  //update the display
  display.display();
  delay(30);
}