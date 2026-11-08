// Blinkster
// 14 Oct 2026
#include "TFT_eSPI.h"
TFT_eSPI tft;
int speedBar=10;
int blinkSpeed = 200;

const int ledPins[] = {BCM0, BCM1, BCM2, BCM3, BCM4, 
                        BCM5, BCM6, BCM7, BCM8, BCM9};

// คำนวณจำนวน LED อัตโนมัติจากขนาด array
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

const int delayTime = 200; // หน่วงเวลาระหว่างดวง (มิลลิวินาที) 
void setup() {
  // put your setu(p code here, to run once:
  pinMode(WIO_5S_LEFT,INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT,INPUT_PULLUP);

  pinMode(BCM0,OUTPUT);
  pinMode(BCM1,OUTPUT);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLUE);
  
  tft.setTextColor(TFT_RED,TFT_YELLOW);
  tft.setTextSize(2);

  // header title
  tft.fillRoundRect(5,5,310,40,2,TFT_YELLOW);
  tft.drawString("640710ฟหก",110,18);

  // footer
  tft.setTextColor(TFT_BLUE,TFT_YELLOW);
  tft.fillRoundRect(5,205,310,30,2,TFT_YELLOW);
  tft.drawString("Uchiha Itachi",85,213);

  Serial.begin(115200);

  // draw the first speed bar block
  tft.fillRoundRect(speedBar,100,28,50,0,TFT_WHITE);
  speedBar = speedBar + 30;
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // เริ่มต้นให้ดับทุกดวงก่อน
  }
}

void loop() {

  for (int i = 0; i < numLeds; i++) {
    if (i < 5) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(blinkSpeed);

  for (int i = numLeds - 1; i >= 0; i--) {
    if (i >= 5) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(blinkSpeed);

  // put your main code here, to run repeatedly:
  if (digitalRead(WIO_5S_LEFT) == LOW) {
    // tft.drawString("LEFT  ",0,10);
    if (speedBar > 40) {
      speedBar = speedBar - 30;
      blinkSpeed = blinkSpeed+20;
      tft.fillRoundRect(speedBar,100,28,50,0,TFT_BLUE);    
      Serial.println(speedBar);   
      Serial.println(blinkSpeed);
    }
    delay(200);
  }
  else if (digitalRead(WIO_5S_RIGHT) == LOW) {
    // tft.drawString("RIGHT",0,10);
    if (speedBar < 310) {
      tft.fillRoundRect(speedBar,100,28,50,0,TFT_WHITE);
      blinkSpeed = blinkSpeed-20;
      speedBar = speedBar + 30;
      Serial.println(speedBar);
      Serial.println(blinkSpeed);
    }
    delay(200);
  } 

  
}
