#include "LedControl.h"

// Set the LED grid pins to specific ports on the Arduino
int DIN = 7;
int CS =  6;
int CLK = 5;

// The button used to generate random numbers
int buttonState = 0;
int buttonPin = 13;

// The button used to sort the numbers
int buttonSortState = 0;
int buttonSortPin = 12;

// The number of rows on the LED grid
int rows = 8;

// The random numbers array used.
int randomNumbers[] = {0,0,0,0,0,0,0,0};

// The LED Matrix object
LedControl lc=LedControl(DIN,CLK,CS,1);

/**
 * Set up the buttons and matrix. Also sets analog pin 0 to be the pin used
 * to gather random values
 */
void setup() {
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  // Sets pins for button inputs
  pinMode(buttonPin, INPUT);
  pinMode(buttonSortPin, INPUT);

   /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call. This is mostly important for battery powered
   devices.   */
  lc.shutdown(0,false);

  /* Set the brightness to a medium value (0-15). 0 does not turn off the     
     grid */
  lc.setIntensity(0,8);

  /* and clear the display (switches all LEDs to off)*/
  lc.clearDisplay(0);
  
}

/**
 * Clears the array and displays the empty screen to the LED matrix.
 */
void clearArray(int arr[]){
  // Sets each row of the LED grid to be 0.
   for(int i = 0; i < rows; i++){
    arr[i] = B00000000;
  }
  
  displayArray(arr);
}

/**
 * Displays the array of bytes in arr to the LED matrix screen.
 */
void displayArray(int arr[]){
  // Uses x as the base value displayed.
  byte x = B00000001;

  // Sets the bit number from arr[index] to be turned on
  // For example arr[i] = 7 then the 7th LED in the row will be on, everything else is off.
  for(int i = 0; i < rows; i++){
    int y = x << arr[i];
    lc.setRow(0,i, y);
    delay(20);
  }
}

/**
 * Sorts the array using bubble sort and displays the steps.
 */
void bubbleSort(int arr[]){

  for(int i = 0; i < rows; i++){
    
    for(int j = 0; j < rows-i - 1; j++){
      
       if (arr[j] > arr[j+1]) {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
      displayArray(arr);
    }
    
  } 
  
}

/**
 * Continuously checks for buttons pressed to either generate numbers or sort the array.
 */
void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  buttonSortState = digitalRead(buttonSortPin);

  // Generate numbers if the first button pressed
  if(buttonState == HIGH){
    clearArray(randomNumbers);

    // Stores 8 random numbers into an index in the array
    for(int i = 0; i < rows; i++){
      randomNumbers[i] = random(0, 8);
    }

    // Displays the array of random numbers
    displayArray(randomNumbers);
  }

  // Sort the array if the second button pressed
  if(buttonSortState == HIGH){
    bubbleSort(randomNumbers);
  }
  
}
