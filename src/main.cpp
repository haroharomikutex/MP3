#include <SD_MMC.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <FFat.h>
#include <Adafruit_NeoPixel.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

#define NEO_GRB     0 // NEOPIXEL LEDストリップのカラーオーダー
#define NEO_KHZ800  800000 // LEDストリップの周波数
#define PIN            15
#define NUMPIXELS      10

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 10; 
int volume = 100;

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

bool flag_mp3IsPlayed = false;



void playStartupMp3(){
    file = new AudioFileSourceSD("/startup.mp3");
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(1.3);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
    while(mp3->isRunning()){
        if (!mp3->loop()) mp3->stop();
    }
}


void play1Mp3(){
    file = new AudioFileSourceSD("/yobikomi1.mp3");
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(1.3);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
    while(mp3->isRunning()){
        if (!mp3->loop()) mp3->stop();
    }
}
void play2Mp3(){
    file = new AudioFileSourceSD("/yobikomi2.mp3");
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(1.3);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
    while(mp3->isRunning()){
        if (!mp3->loop()) mp3->stop();
    }
}
void play3Mp3(){
    file = new AudioFileSourceSD("/1.mp3");
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(1.3);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
    while(mp3->isRunning()){
        if (!mp3->loop()) mp3->stop();
    }
}
void setup()
{
    Serial.begin(115200);
    delay(10);
    pinMode(36,INPUT);

    M5.begin();

    // SDカードの初期化
    if (!SD.begin()) {
        Serial.println("Card Mount Failed");
        return;
    }
    Serial.println("Card Initialized");

    
        playStartupMp3();

    // 画面にPNGファイルを表示
    //M5.Lcd.drawJpgFile(SD, "/1.png");
}

void loop()
{
    M5.update();

    if(M5.BtnA.isPressed()||digitalRead(36) == 1){
        play1Mp3();
        flag_mp3IsPlayed = true;
    }
        if(M5.BtnB.isPressed()){
        play2Mp3();
        flag_mp3IsPlayed = true;
    }
         if(M5.BtnC.isPressed()){
        play3Mp3();
        flag_mp3IsPlayed = true;
    }   
  
    // LEDストリップの点灯処理
    int color_r = random(255);
    int color_g = random(255);
    int color_b = random(255);
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b)); 
        pixels.show(); 
    }
  
    delay(100); // 点灯時間
    pixels.clear(); // LEDを消灯するために全てのピクセルをクリア
    pixels.show(); // LEDを更新して消灯させる
    delay(100); // 消灯時間

    // 画面更新処理
   // M5.Lcd.drawPngFile(SD, "/1.png");

    delay(100);
}
