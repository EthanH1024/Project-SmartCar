#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>
#include <ultrasonic.h>
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
int UT_distance =0; 
int myServo_PIN =27;
int leftDistance=0;
int middleDistance =0;
int rightDistance =0;

void ledLights() {{
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


void ultrasonicMovement(){
UT_distance = myUltrasonic.Ranging();
  if(UT_distance<= 25)
  { myCar.Move(Contrarotate,180);
  delay(1500);
  myCar.Move(Stop,0);
  }
  else{
myCar.Move(Forward,150);
  }
  Serial.print(UT_distance);
  Serial.println("cm");
  delay(1000);

 /* for(int angle =0;angle<=180;angle++){
    myServo.write(angle);
    delay(10);
  }
  for(int angle =180;angle>=0;angle--){
myServo.write(angle);
delay(10);
  }*/
   }
  
  void objectAdvoidise(){
middleDistance =myUltrasonic.Ranging();
myServo.write(90);
if(middleDistance<=25){
myCar.Move(stop,0);
myServo.write(0);
for(int angle =90;angle>=0;angle--){
  myServo.write(angle);
  delay(10);
}
}
delay(500);
rightDistance =myUltrasonic.Ranging();
for(int angle =0;angle<=180;angle++){
myServo.write(angle);
delay(10);
}
  }



void setup()
{
  Serial.begin(11520);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  analogWrite(leftLED, 50);
  analogWrite(rightLED, 50);

  myServo.write(0);
  myServo.attach(servoPin);
  myCar.Init();

  Serial.begin(9600);
  myUltrasonic.Init(13,14);
  myServo.attach(myServo_PIN);//initialize servo motor
  myServo.write(0);

  myServo.attach(myServo_PIN);
}

void loop()
{ // put your main code here, to run repeatedly:
  ledLights();
  ultrasonicMovement();
objectAdvoidise();


  delay(100);
}
 
   