#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>


/*
myCar.Move(forward,255);
myCar.Move(Backward,255);

myCar.Move(Move_Right,255);
myCar.Move(Move_Left,255);

myCar.Move(Clockwise,255);
myCar.Move(Contrarotate,255);


myCar.Move(Stop,0);


*/




vehicle myCar;
Servo myServo;


#define leftLED 2
#define rightLED 12
#define buzzer 33
#define servoPin 25
const int fadedelay=10;


void setup()
{
 Serial.begin(11520);
pinMode(leftLED,OUTPUT);
pinMode(rightLED,OUTPUT);

analogWrite(leftLED,50);
analogWrite(rightLED,50);

myServo.write(0);
myServo.attach(servoPin);
myCar.Init();

}

void loop()
{
  // put your main code here, to run repeatedly:
digitalWrite(leftLED,HIGH);
digitalWrite(rightLED,LOW);
{
for (int brightness=0;brightness<= 255;brightness++)
analogWrite(leftLED,brightness);
analogWrite(rightLED,brightness);
delay(fadedelay);
}
//myCar.Move(Move_Left,255);
//tone(buzzer,262);
delay(1000);

digitalWrite(leftLED,LOW);
digitalWrite(rightLED,HIGH);
//myCar.Move(Move_Right,255);
//noTone(buzzer);
{
for (int brightness=255;brightness>=0;brightness--)
analogWrite(leftLED,brightness);
analogWrite(rightLED,brightness);
delay(fadedelay);
}
delay(1000);


  delay(100);
}

