#include <Servo.h>
#include <IRremote.h>
#include "MotorController.h"

#define FULL_TURN_TIME 700

// Servo
Servo Myservo;
int angle = 90;

// IR reciver
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

MotorController MC(2, 4, 7, 8, A4, A5);


// Ultra Sonic
#define TRIG_PIN A1
#define ECHO_PIN A0
int USResult;

float checkdistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  float distance = pulseIn(ECHO_PIN, HIGH) / 58.00;
  delay(10);
  return distance;
}



void setup() {
  // put your setup code here, to run once:
  Myservo.attach(A2);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

  MC.SetAction('F', 10000);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

  if (results.value == 0xFF629D){
    angle += 30;
    results.value = 0x000000;
  }
  if (results.value == 0xFFA857){
    angle -= 30;
    results.value = 0x000000;
  }

  Serial.println(checkdistance());

  MC.RunMotors();


  Serial.println(MC.getCurrentAction());

  Myservo.write(angle);
}
