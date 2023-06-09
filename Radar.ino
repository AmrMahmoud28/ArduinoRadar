// Includes the Servo library
#include <Servo.h>.
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 3;
const int echoPin = 5;
const int buttonPin = 2;
// Variables for the duration and the distance
long duration;
int distance;
boolean buttonState = true;
Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buttonPin, INPUT);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}

void loop() {
  isButtonPressed();
  while(buttonState){
    // rotates the servo motor from 15 to 165 degrees
    for (int i = 15; i <= 165; i++) {
      isButtonPressed();
      if(buttonState == false){
        break;
      }
      myServo.write(i);
      delay(30);
      distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
      if(distance > 5 || distance <= 100){
        Serial.print(i); // Sends the current degree into the Serial Port
        Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
        Serial.print(distance); // Sends the distance value into the Serial Port
        Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      }
    }
    if(buttonState == false){
        break;
    }
    // Repeats the previous lines from 165 to 15 degrees
    for (int i = 165; i > 15; i--) {
      isButtonPressed();
      if(buttonState == false){
        break;
      }
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      if(distance > 5 || distance <= 100){
        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
      }
    }
    delay(50);
  }
  delay(100);
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH,50000); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;

  if(distance <= 5){
    distance = 5;
  }
  else if(distance >= 100){
    distance = 100;
  }
  
  return distance;
}

void isButtonPressed(){
  if(digitalRead(buttonPin) == 1){
    buttonState = !buttonState;
    delay(1000);
  }
}
