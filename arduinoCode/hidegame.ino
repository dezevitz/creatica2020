#include "SR04.h"

//Specify Pins
int trig_pin = A1;
int echo_pin = A2;
int buzzerPin = A0;

// Digit Pins
#define GREEN 2
#define RED 4
#define BLUE 5
int buttonOnPin = 3;
boolean gameOver = false;

int greenVal = 0;
int redVal = 0;
int blueVal = 255;
SR04 sensor = SR04(echo_pin,trig_pin);

//reset Button
int resetButton = 6;

//score
int rWins = 0;
int r1 = 7;
int r2 = 8;
int r3 = 9;
int cooldown = 0;

int gWins = 0;
int g1 = 10;
int g2 = 11;
int g3 = 12;

long distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  delay(1000);

  // initalize pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(buttonOnPin, INPUT_PULLUP);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  boolean gameOver = false;

  //reset Button
  pinMode(resetButton, INPUT_PULLUP);
}

void loop() {
  analogWrite(RED, redVal);
  analogWrite(GREEN, greenVal);
  analogWrite(BLUE, blueVal);
  
  if (digitalRead(buttonOnPin) == LOW){
    gameOver =  true;
    if (cooldown == 0){
      rWins += 1;
      cooldown = 1;
    }
  }
  if (gameOver == true){
    redVal = 255;
    greenVal = 0;
    blueVal = 0;
    digitalWrite(buzzerPin, HIGH);
    delay(1);
    digitalWrite(buzzerPin, LOW);
    delay(1);
  }
  else if (greenVal < 255){
    greenVal += 1;
    blueVal -= 1;

    //Sensor code
    distance=sensor.Distance();
    Serial.println(distance);
    digitalWrite(buzzerPin, HIGH);
    delay(3);
    digitalWrite(buzzerPin, LOW);
    if (distance < 2000){
    delay(distance*2);
    }
  }
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

  if (digitalRead(resetButton) == LOW){
    redVal = 0;
    greenVal = 0;
    blueVal = 255;
    gameOver = false;
    cooldown = 0;

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

  if (rWins == 1){
    analogWrite(r1, 225);
  }
  else if (rWins == 2){
    analogWrite(r2, 225);
  }
  else if (rWins == 3){
    analogWrite(r3, 225);
  }
  if (gWins == 1){
    analogWrite(g3, 225);
  }
  else if (gWins == 2){
    analogWrite(g2, 225);
  }
  else if (gWins == 3){
    analogWrite(g1, 225);
  }
  
}
