#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ── Display ──────────────────────────────────────────
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ── Joystick ─────────────────────────────────────────
#define JOY_X   A0
#define JOY_Y   A1
#define JOY_BTN 2
test
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
  delay(1500);
}
int speed=0;
void loop() {
  // ── Read joystick ───────────────────────────────────
  int joy_x   = analogRead(JOY_X);         // 0 - 1023
  int joy_y   = analogRead(JOY_Y);         // 0 - 1023
  bool btn    = !digitalRead(JOY_BTN);     // true when pressed
  // ── Draw ────────────────────────────────────────────
  display.clearDisplay();

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
    display.print((char)7);//center => square symbol
  }
  display.setCursor(10,0);
  display.print("--the pico book--");

  display.setCursor(0, 20);
  display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
  display.setCursor(1, 20);
  display.print("Lorem");

  display.setCursor(SCREEN_WIDTH-11*5, SCREEN_HEIGHT-10);
  display.print("speed:");
  char buffer[4];
  sprintf(buffer,"%3d", speed);
  display.print(buffer);

  display.display();
  delay(30);
}