#include "LedControl.h"
#include <arduino-timer.h>

int buttonState = 0;

int buttonPin = 3;
int rows = 8;

int DIN = 10;
int CS =  11;
int CLK = 12;

int randNum = 0;
int address = 0;
int counter = 0;
byte state[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
float birdPosition = 0;
float gravity = 0.1;

int score = 0;

boolean gameOver = false;

// The LED Matrix object
LedControl lc = LedControl(DIN,CLK,CS,1);
auto timer = timer_create_default();

void setup() {
  // Sets pins for button inputs
  pinMode(buttonPin, INPUT);
randomSeed(analogRead(0));
Serial.begin(9600);
 /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(address,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(address,8);
  /* and clear the display */
  lc.clearDisplay(address);

  timer.every(500, shiftScreen);
  timer.every(50, displayScreen);

}

byte generateBar(){
  randNum = random(0,6);
  byte newColumn = B00000000;
  
  for(int i = 0; i < rows; i++){
    newColumn = newColumn << 1;
    if(i < randNum || i > randNum + 3){
     newColumn++;
     
    }
    
  }
  return newColumn;
}
int count = 0;
void shiftScreen(){
   count = (count + 1)%5;
   for(int i = rows - 1; i > 0; i--){
    state[i] = state[i-1];
  }
  if(count == 0){
    state[0] = generateBar();
    score++;
  }
   else {
    state[0] = B00000000;
   }
}

void displayScreen(){
 if(!gameOver){
  for(int i = 0; i < rows; i++){
    lc.setRow(address, i, state[i]);
  }


  lc.setRow(address, 6,combinedRow(state[6], birdRow()));
}
  delay(100);
}

void setAll(byte input){
   for(int i = 0; i < 10; i++){
      lc.setRow(address, i, input);
   }
}

void restartGame(){
  timer.every(500, shiftScreen);
  timer.every(50, displayScreen);

  for(int i = 0; i < 8; i++){
    state[i] = 0x00;
  }
}

byte combinedRow(byte b1, byte b2){
  byte x = B00000000;
  for(int i = 7; i >= 0; i--){
    x = x << 1;
    if(bitRead(b1,i) == 1 && bitRead(b2,i) == 1){
      timer.cancel();
      gameOver = true;
      
      for(int i = 0; i < 10; i++){
        if(i % 2==0){
          setAll(0xFF);
        } else {
          setAll(0x00);
        }
        delay(150);
      }
      x = 0x00;

      displayScore(score);
      score = 0;
    }
    else if(bitRead(b1,i) == 1 || bitRead(b2,i) == 1){
      
      x = x + B00000001;
    }
   
  }
  return x;
}
void displayScore(int score){
  score -=2;
  int rowNum = score / 8;
  int rem = score % 8;
  
  setAll(0x00);
  
  for(int i = 0; i < rowNum; i++){
    lc.setRow(address, i, 0xFF);
  }

  byte x = 0x00;
  for(int i = 0; i < rem; i++){
    x = (x << 1) + 1;
  }

  lc.setRow(address,rowNum, x);
  delay(100);

  
}
byte birdRow(){
  if(birdPosition >=7) return B10000000;
  if(birdPosition <=0) return B00000001;
  
  return B00000001 << (int)birdPosition;
}

void updateBirdPosition(){
  if(buttonState == LOW){
     
    if(birdPosition <= 0){
     birdPosition = 0;
      
    }else {
      birdPosition -= (6*gravity);
    }
    
  } else{
    if(birdPosition > 7){
      birdPosition = 7;
    } else {
     birdPosition += 9*gravity;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  buttonState = digitalRead(buttonPin);
  if(!gameOver){
    updateBirdPosition();
    timer.tick();
    
  } else {
    if(buttonState == HIGH){
      restartGame();
      gameOver = false;
    }
  }

  
 


}
