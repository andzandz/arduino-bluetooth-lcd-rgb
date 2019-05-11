#include <LiquidCrystal.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            13


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

int red = 0, green = 0, blue = 0;
boolean funky = false;

const int 
  rs = A0, 
  en = A5, 
  d4 = A1, 
  d5 = A2, 
  d6 = A3, 
  d7 = A4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String str_buffer = "";
char incoming_byte = 0;   // for incoming serial data

String screen_text[4] = {"Hello world!","","",""};
int screen_current_line = 0; // top line

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  pixels.begin(); // This initializes the NeoPixel library.

  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
}

void clearScreen() {
  screen_text[0] = "                    ";
  screen_text[1] = "                    ";
  screen_text[2] = "                    ";
  screen_text[3] = "                    ";
  screen_current_line = -1;
}

void showOnScreen(String text) {
  while(text.length() < 20) {
    text = text + " ";
  }
  
  if(screen_current_line < 3) {
    screen_current_line++;
  } else {
    // move all the text up
    screen_text[0] = screen_text[1];
    screen_text[1] = screen_text[2];
    screen_text[2] = screen_text[3];
  }
  screen_text[screen_current_line] = text;
}

int hexCharToInt(char hex_char) {
  if(hex_char >= 48 && hex_char <= 57) {
    return hex_char - 48; 
  }
  if(hex_char >= 97 && hex_char <= 102) {
    return 10 + hex_char - 97;
  }
  return 0;
}

void serialCommandReceived(String command) {
  Serial.println("Got: " + command);

  if(command[0] == '/') {
    if(command == "/clear") {
      clearScreen();
    } else if(command == "/funky") {
      funky = true;
    } else if(str_buffer[1] == 'R') {
      red = str_buffer.substring(2).toInt();
    } else if(str_buffer[1] == 'G') {
      green = str_buffer.substring(2).toInt();
    } else if(str_buffer[1] == 'B') {
      blue = str_buffer.substring(2).toInt();
    } else {
      if(command.length() == 4) {
        funky = false;
        red = hexCharToInt(command[1])*17;
        green = hexCharToInt(command[2])*17;
        blue = hexCharToInt(command[3])*17;
      }
    }
  } else {
    while(command.length() > 20) {
      showOnScreen(command.substring(0,20)); // ends before 20
      command = command.substring(20); // starts from 20
    }
    showOnScreen(command);
  }
}

void readSerial() {
  while(Serial.available() > 0) {
    incoming_byte = Serial.read();
    if(incoming_byte == '\r') {
      // ignore
    } else if(incoming_byte != '\n') {
      str_buffer += incoming_byte;
    } else {
      serialCommandReceived(str_buffer);
      str_buffer = "";
    }
  }
}

void loop() {
  readSerial();

  for (int i=0; i<4; i++) {
    lcd.setCursor(0, i);
    lcd.print(screen_text[i]);
  }
  if(funky) {
    int colour_n = (millis() / 333) % 7 ;
    if(colour_n == 0) pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    if(colour_n == 1) pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    if(colour_n == 2) pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    if(colour_n == 3) pixels.setPixelColor(0, pixels.Color(0, 255, 255));
    if(colour_n == 4) pixels.setPixelColor(0, pixels.Color(255, 0, 255));
    if(colour_n == 5) pixels.setPixelColor(0, pixels.Color(255, 255, 0));
    if(colour_n == 6) pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  } else {
    pixels.setPixelColor(0, pixels.Color(red, green, blue));
  }
  pixels.show();
}


