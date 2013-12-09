//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Using the easy stepper with your arduino
//use rotate and/or rotateDeg to controll stepper motor
//speed is any number from .01 -> 1 with 1 being fastest - 
//Slower Speed == Stronger movement
/////////////////////////////////////////////////////////////////


#define DIR_PIN   2
#define STEP_PIN  3
//#define blue      5
//#define green     10
//#define red       6
int colors[3] = {6, 10, 5};
boolean dir = true;
unsigned long timeLedChanged = millis();
int fadeValue = 0;
int col = 0;
int pin = 0;

int sensorValue = 0;
float omega = 0;

void setup() { 
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT); 
  Serial.begin(9600);
/*  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT); /**/

} 

void loop(){ 
  sensorValue = analogRead(A0);
  omega = sensorValue * (1.0 / 1023.0); //read the analog and convert to decimal
  rotate(1, omega); //number of steps to rotate, rotation speed based on analog
  fader(90,1,colors); //delay between steps, fade step size, color array
  //  delay(1000);
}

void fader(int del, int inc, int* cols) {
  if (millis() - timeLedChanged >= del) {   //check to see if the time is right to increase the fade
    timeLedChanged = millis();
    if (dir) {                              //if it is fading up, do this
      if (fadeValue == 250) {
        dir = !dir;                         //if you hit 250, reverse fade direction
      }
      fadeValue += inc;                     //incriment the fade 
    } 
    else {
      if (fadeValue == 5) {
        dir = !dir;                         //if you hit 5, reverse fade direction
        pin = cols[col];
        if (col == 2) {                     //once you have gone through all 3 colors, go back to the first one
          col = 0;
        } 
        else {
          col+=1;                           //change the fade color pin by one
        }
      }
      fadeValue -= inc;
    }
    analogWrite(pin, fadeValue);            //tell the pin to PWM that color
/*    Serial.print("Fade: ");
    Serial.println(fadeValue);
    Serial.print("color: ");
    Serial.println(col); /**/
  }
}

void rotate(int steps, float speed){ 
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN,dir); 

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
} 







