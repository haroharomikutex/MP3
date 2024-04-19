#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <M5Unified.h>
#include <DFRobotDFPlayerMini.h>
#include <SD.h>

#define NEO_GRB     0 // NEOPIXEL LEDストリップのカラーオーダー
#define NEO_KHZ800  800000 // LEDストリップの周波数
#define PIN            15
#define NUMPIXELS      10

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 10; 
int volume = 1;

DFRobotDFPlayerMini player;

void setup() {
  M5.begin();
  M5.Power.begin();
  pixels.begin();
  pinMode(36, INPUT);

  if (!SD.begin()) {
    M5.Lcd.println("SD Card initialization failed!");
    return;
  }
  
  if (!player.begin(Serial2)) {
    M5.Lcd.println("Unable to begin DFPlayer Mini");
    while(true);
  }
  
  player.volume(50);  // Set volume level (0~30).
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(30,120);
  M5.update();
  
  int color_r = random(255);
  int color_g = random(255);
  int color_b = random(255);
  
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b)); 
    pixels.show(); 
    delay(delayval);
  }
  
  if(M5.BtnA.wasPressed()) {
    playMP3();
  }
  
  if(M5.BtnC.wasPressed()) {
    player.stop();
  }
  
  if(digitalRead(36) == 1) {
    M5.Lcd.clear();
    M5.Lcd.print("!!!");
    // Do something when sensor is triggered
  }
  
  M5.delay(10);
}

void playMP3() {
  File root = SD.open("/");
  File file = root.openNextFile();
  
  while(file) {
    String fileName = file.name();
    
    if(fileName.endsWith(".mp3")) {
      // ファイル名が ".mp3" で終わる場合、再生を開始する
      player.play(fileName.c_str()); // ファイル名を文字列として渡す
      return;
    }
    
    file = root.openNextFile();
  }
}
