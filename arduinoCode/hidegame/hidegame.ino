#include "SR04.h" // this file contains code for the untrosonic sensor

// Sensor Pins
int trig_pin = A1;
int echo_pin = A2;
int buzzerPin = A0;

// Color changing LED
#define GREEN 2
#define RED 4
#define BLUE 5
int buttonOnPin = 3;
boolean gameOver = false;
int greenVal = 0;
int redVal = 0;
int blueVal = 255;

// Sensor
SR04 sensor = SR04(echo_pin,trig_pin);
long distance;

//reset Button
int resetButton = 6;

//score
int rWins = 0; //red
int r1 = 7;
int r2 = 8;
int r3 = 9;
int cooldown = 0;

int gWins = 0; //green
int g1 = 10;
int g2 = 11;
int g3 = 12;

void setup() {

  //sensor setup
  Serial.begin(9600);

  //buzzer setup
  pinMode(buzzerPin, OUTPUT);
  delay(1000);

  // initalize color changing colors RGB
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // initialize Attacker's button to take input
  pinMode(buttonOnPin, INPUT_PULLUP);

  //Start color changer with no color
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  //initialize gameOver sequence as false
  boolean gameOver = false;

  //initialize reset Button
  pinMode(resetButton, INPUT_PULLUP);
}

void loop() {

  //Displays color changing light with appropriate color
  analogWrite(RED, redVal);
  analogWrite(GREEN, greenVal);
  analogWrite(BLUE, blueVal);

  //when attacker button is pressed
  if (digitalRead(buttonOnPin) == LOW){
    gameOver =  true;
    if (cooldown == 0){
      rWins += 1;
      cooldown = 1;
    }
  }

  //end round sequence for Attacker wins
  if (gameOver == true){
    redVal = 255;
    greenVal = 0;
    blueVal = 0;
    digitalWrite(buzzerPin, HIGH);
    delay(1);
    digitalWrite(buzzerPin, LOW);
    delay(1);
  }
  //Else if, make the color changing light more green
  else if (greenVal < 255){
    greenVal += 1;
    blueVal -= 1;

    //Sensor code based on distance
    distance=sensor.Distance();
    Serial.println(distance);
    digitalWrite(buzzerPin, HIGH);
    delay(3);
    digitalWrite(buzzerPin, LOW);
    if (distance < 30){
      delay(5);
    }
    else if (distance < 50){
      delay(20);
    }
    else if (distance < 100){
      delay(100);
    }
    else if (distance < 200) {
      delay(250);
    }
    else if (distance > 2000){
      delay(100);
    }
    else {
      delay(1000);
    }
   
  }
  //if green wins
  else if (greenVal = 255){
    digitalWrite(buzzerPin, HIGH);
    delay(1);
    digitalWrite(buzzerPin, LOW);
    delay(1);
    if (cooldown == 0){
      gWins += 1;
      cooldown = 1;
    }
  }
  
  //the reset button is pressed
  if (digitalRead(resetButton) == LOW){
    redVal = 0;
    greenVal = 0;
    blueVal = 255;
    gameOver = false;
    cooldown = 0;
    //if reset button is pressed, and there is a winner
    if (rWins == 3 or gWins == 3){
      rWins = 0;
      gWins = 0;
      analogWrite(r1, 0);
      analogWrite(r2, 0);
      analogWrite(r3, 0);
      analogWrite(g1, 0);
      analogWrite(g2, 0);
      analogWrite(g3, 0);
    }
  }

// This code turns on the appropriate lights to show how many rounds have been won
  if (rWins == 1){ //red
    analogWrite(r1, 225);
  }
  else if (rWins == 2){
    analogWrite(r2, 225);
  }
  else if (rWins == 3){
    analogWrite(r3, 225);
  }
  if (gWins == 1){ //green
    analogWrite(g3, 225);
  }
  else if (gWins == 2){
    analogWrite(g2, 225);
  }
  else if (gWins == 3){
    analogWrite(g1, 225);
  }
  
}
