#include "LedControl.h"

byte one[] = { 0x00, 0x00, 0x00, B00011000, B00011000, 0x00, 0x00, 0x00 };
byte two[] = { 0x00, B01100000, B01100000, 0x00, 0x00, B00000110, B00000110, 0x00 };
byte three[] = { 0x00, B01100000, B01100000, B00011000, B00011000, B00000110, B00000110, 0x00 };
byte four[] = { 0x00, B01100110, B01100110, 0x00, 0x00, B01100110, B01100110, 0x00 };
byte five[] = { 0x00, B01100110, B01100110, B00011000, B00011000, B01100110, B01100110, 0x00 };
byte six[] = { B01100110, B01100110, 0x00, B01100110, B01100110, 0x00, B01100110, B01100110 };

byte arr[6][8] = {{ 0x00, 0x00, 0x00, B00011000, B00011000, 0x00, 0x00, 0x00 },
        { 0x00, B01100000, B01100000, 0x00, 0x00, B00000110, B00000110, 0x00 },
         { 0x00, B01100000, B01100000, B00011000, B00011000, B00000110, B00000110, 0x00 },
         { 0x00, B01100110, B01100110, 0x00, 0x00, B01100110, B01100110, 0x00 },
         { 0x00, B01100110, B01100110, B00011000, B00011000, B01100110, B01100110, 0x00 },
         { B01100110, B01100110, 0x00, B01100110, B01100110, 0x00, B01100110, B01100110 }};

int buttonState = 0;

int buttonPin = 3;

int DIN = 10;
int CS =  11;
int CLK = 12;

int address = 0;


// The LED Matrix object
LedControl lc = LedControl(DIN,CLK,CS,1);

void setup() {
  // Sets pins for button inputs
  pinMode(buttonPin, INPUT);

  randomSeed(analogRead(0));

 /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(address,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(address,8);
  /* and clear the display */
  lc.clearDisplay(address);
 
}

void selectValue(int randVal){

  
  // Sets the bit number from arr[index] to be turned on
  // For example arr[i] = 7 then the 7th LED in the row will be on, everything else is off.
  for(int i = 0; i < 8; i++){
   
    lc.setRow(0,i, arr[randVal][i]);
    delay(20);
    
 }

  
}



void loop() {
  buttonState = digitalRead(buttonPin);
  
  if(buttonState == HIGH){
      int randVal = random(0,6);
    //pressAnimation();
    selectValue(randVal);
  }

}
