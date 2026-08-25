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

#define leftLED 2
#define rightLED 12
#define buzzer 33
#define servoPin 25
#define IRpin 4
IRrecv myIRrecv(IRpin);

const int fadedelay = 10;
int UT_distance = 0;

int leftDistance = 0;
int middleDistance = 0;
int rightDistance = 0;

void ledLights()
{
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
}

void objectAdvoidise()
{
  myServo.write(90);
  middleDistance = myUltrasonic.Ranging();
  Serial.println(middleDistance);
  if (middleDistance <= 25)
  {
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

    // Decide direction based on clear space
    if (rightDistance < 20 && leftDistance < 20)
    {
      myCar.Move(Backward, 180);
      delay(500);
      myCar.Move(Contrarotate, 180);
      delay(1000);
    }
    else if (rightDistance > leftDistance)
    {
      // Right side has more room
      myCar.Move(Clockwise, 180);
      delay(800);
    }
    else
    {
      // Left side has more room (or equal)
      myCar.Move(Contrarotate, 180);
      delay(800);
    }
  }
  else
  {
    myCar.Move(Forward, 150);
  }
}

/*middleDistance =myUltrasonic.Ranging();
myServo.write(90);
if(middleDistance<=25){
myCar.Move(Stop,0);
myServo.write(0);
for(int angle =90;angle>=0;angle--){
myServo.write(angle);
delay(10);
}

delay(500);
rightDistance =myUltrasonic.Ranging();
for(int angle =0;angle<=180;angle++){
myServo.write(angle);
delay(10);
}
delay(500);
leftDistance =myUltrasonic.Ranging();
if(rightDistance<20&& leftDistance<20){
myCar.Move(Backward,180);
delay(500);
myCar.Move(Contrarotate,180);
delay(1000);
}
else if(rightDistance< leftDistance){
myCar.Move(Backward,180);
delay(500);
myCar.Move(Clockwise,180);
delay(1000);
}
else if(rightDistance< leftDistance){
myCar.Move(Backward,180);
delay(500);
myCar.Move(Contrarotate,180);
delay(1000);
}
else{
myCar.Move(Backward,180);
delay(500);
myCar.Move(Clockwise,180);
delay(1000);
}
}
else{
myCar.Move(Forward,150);
}
}*/

void setup()
{
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  analogWrite(leftLED, 50);
  analogWrite(rightLED, 50);

  myServo.attach(servoPin);
  myServo.write(0);
  myCar.Init();

  Serial.begin(115200);
  myUltrasonic.Init(13, 14);
}

void loop()
{ // put your main code here, to run repeatedly:
  // ledLights();
  objectAdvoidise();

  delay(100);
}
