#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>
#include <IRremote.h>

/*
myCar.Move(forward,255);
myCar.Move(Backward,255);

myCar.Move(Move_Right,255);
myCar.Move(Move_Left,255);

myCar.Move(Clockwise,255);
myCar.Move(Contrarotate,255);

// myCar.Move(Move_Right,255);
  // noTone(buzzer);

 // myCar.Move(Move_Right,255);
  // noTone(buzzer);

myCar.Move(Stop,0);


*/

vehicle myCar;
Servo myServo;
ultrasonic myUltrasonic;

const int RECV_PIN = 4; // Check your specific ESP32 pin in your manual (e.g., 19 or 32)
bool obstacleAvoidanceEnabled = false; // Toggle state variable 


#define leftLED 2
#define rightLED 12
#define buzzer 33
#define servoPin 25
#define IRpin 4


const int fadedelay = 10;
int UT_distance = 0;

int leftDistance = 0;
int middleDistance = 0;
int rightDistance = 0;

/*void ledLights() {
  {
    for (int brightness = 0; brightness <= 255; brightness++)
    {
      digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, LOW);
      analogWrite(leftLED, brightness);
      analogWrite(rightLED, brightness);
      delay(fadedelay);
    }
  }
  delay(1000);

  {
    for (int brightness = 255; brightness >= 0; brightness--)
    {
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, HIGH);
      analogWrite(leftLED, brightness);
      analogWrite(rightLED, brightness);
      delay(fadedelay);
    }
  }
  delay(1000);
}*/
void objectAdvoidise()
{
  myServo.write(90);
  middleDistance = myUltrasonic.Ranging();
  Serial.println(middleDistance);
  if (middleDistance <= 25)
  {
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, HIGH);
    myCar.Move(Stop, 0);
 

    // Look right
    myServo.write(0);
    delay(500);
    rightDistance = myUltrasonic.Ranging();

    // Look left
    myServo.write(180);
    delay(500);
    leftDistance = myUltrasonic.Ranging();

    // Reset servo to center
    myServo.write(90);
digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);

    // Decide direction based on clear space
    if (rightDistance < 20 && leftDistance < 20)
    {
    
     
      myCar.Move(Backward, 180);
       for (int i = 0; i < 2; i++) {
        digitalWrite(leftLED, HIGH);
        digitalWrite(rightLED, HIGH);
        delay(125);
        digitalWrite(leftLED, LOW);
        digitalWrite(rightLED, LOW);
        delay(125);
}
      delay(125);

 for (int i = 0; i < 2; i++) {
        digitalWrite(leftLED, HIGH);
        digitalWrite(rightLED, HIGH);
        delay(125);
        digitalWrite(leftLED, LOW);
        digitalWrite(rightLED, LOW);
        delay(125);
}
     myCar.Move(Contrarotate, 180);
      delay(1000);
     digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, LOW);  

    }
    else if (rightDistance > leftDistance)
    {
      // Right side has more room
       digitalWrite(rightLED, HIGH);
      digitalWrite(leftLED, LOW);
      myCar.Move(Clockwise, 180);
      delay(800);
     digitalWrite(rightLED, LOW); // Turn off when finished
    }
    else
    {
      // Left side has more room (or equal)
       digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, LOW);
      myCar.Move(Contrarotate, 180);
      delay(800);
      digitalWrite(leftLED, LOW); // Turn off when finished
   
    }
  }
  else
  {
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
    myCar.Move(Forward, 150);
  }
}
void remoteChange(){
  // Check if an IR signal is received
  if (IrReceiver.decode()){
    unsigned long irValue = IrReceiver.decodedIRData.decodedRawData;
    
    // Print hex code to serial monitor for verification
    Serial.println(irValue, HEX);

    // Check if the OK button (bf40ff00) is pressed
    if (irValue == 0xBF40FF00) {
      obstacleAvoidanceEnabled = !obstacleAvoidanceEnabled; // Toggle ON/OFF state
      
      if (!obstacleAvoidanceEnabled) {
        myCar.Move(Stop, 0); // Stop the car immediately when turned off
      }
}}
IrReceiver.resume(); // CRITICAL: Receive the next value

}
  


void setup()
{
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  digitalWrite(leftLED, 50);
  digitalWrite(rightLED, 50);

  myServo.attach(servoPin);
  myServo.write(0);
  myCar.Init();

  Serial.begin(115200);
  myUltrasonic.Init(13, 14);

   IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  }
  


void loop()
 {
  // put your main code here, to run repeatedly:
  // ledLights();
  objectAdvoidise();
  remoteChange();
  if (obstacleAvoidanceEnabled) {
    
  }
  delay(100);
 }
