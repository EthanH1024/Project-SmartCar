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

#define leftLED 2
#define rightLED 12




void setup()
{
 Serial.begin(11520);
pinMode(leftLED,OUTPUT);
pinMode(rightLED,OUTPUT);

myCar.Init();

}

void loop()
{
  // put your main code here, to run repeatedly:
digitalWrite(leftLED,HIGH);
digitalWrite(rightLED,LOW);
//myCar.Move(Move_Left,255);
delay(1000);

digitalWrite(leftLED,LOW);
digitalWrite(rightLED,HIGH);
//myCar.Move(Move_Right,255);
delay(1000);


  delay(100);
}

