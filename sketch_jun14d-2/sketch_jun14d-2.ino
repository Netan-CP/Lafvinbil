#include <Servo.h>
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MotorController.h"
#include <string.h>

#define FULL_TURN_TIME 700

// Servo
Servo Myservo;
int angle = 90;

// IR reciver
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

MotorController MC(2, 4, 7, 8, 10, 11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
char writer[36];

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

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(writer);

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

  MC.SetAction('F', 1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

  if (results.value == 0xFF22DD){
   MC.SetAction('L', 500);

    results.value = 0x000000;
  }
  if (results.value == 0xFFC23D){
    MC.SetAction ('R', 500);
    results.value = 0x000000;
  }
  if (results.value == 0xFF629D){
    MC.SetAction ('F', 500);
    results.value = 0x000000;
  }
  if (results.value == 0xFFA857){
    MC.SetAction ('B', 500);
    results.value = 0x000000;
  }

  MC.RunMotors();

  if (strcmp(writer, MC.getCurrentAction())){
    strcpy(writer, MC.getCurrentAction());
    Serial.println(writer);
    lcd.clear();
    lcd.print(writer);
  }
  Myservo.write(angle);
}
