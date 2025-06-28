#include "Arduino.h"
#include "MotorController.h"


MotorController::MotorController(int m_LF, int m_LB, int m_RF, int m_RB, int m_LS, int m_RS){

  M_LF = m_LF;
  M_LB = m_LB;
  M_RF = m_RF;
  M_RB = m_RB;
  M_LS = m_LS;
  M_RS = m_RS;

  pinMode(m_LF, OUTPUT);
  pinMode(m_LB,OUTPUT);
  pinMode(m_RF,OUTPUT);
  pinMode(m_RB,OUTPUT);

  pinMode(m_LS, OUTPUT);
  pinMode(m_RS, OUTPUT);
}

MotorController::~MotorController(){}

void MotorController::Stop(){    
  digitalWrite(M_LF, LOW);
  digitalWrite(M_LB, LOW);
  digitalWrite(M_RF, LOW);
  digitalWrite(M_RB, LOW);
}

void MotorController::Forward(){
  digitalWrite(M_LF, HIGH);
  digitalWrite(M_LB, LOW);
  digitalWrite(M_RF, HIGH);
  digitalWrite(M_RB, LOW);
}

void MotorController::Backward(){
  digitalWrite(M_LF, LOW);
  digitalWrite(M_LB, HIGH);
  digitalWrite(M_RF, LOW);
  digitalWrite(M_RB, HIGH);
}

void MotorController::Turnleft(){

  digitalWrite(M_LF, LOW);
  digitalWrite(M_LB, HIGH);
  digitalWrite(M_RF, HIGH);
  digitalWrite(M_RB, LOW);

}
void MotorController::Turnright(){
  digitalWrite(M_LF, HIGH);
  digitalWrite(M_LB, LOW);
  digitalWrite(M_RF, LOW);
  digitalWrite(M_RB, HIGH);
}


void MotorController::SetAction(char* Name, int Time){
  CurrentAction = Name;
  ActionLength = Time;
  ActionStartTime = millis();
  
  if (Name == 'F') {
    Forward();
  }

  else if(Name == 'B'){
    Backward();
  }

  else if (Name == 'L'){
    Turnleft();
  }
    
  else if (Name == 'R'){
    Turnright();
  }

  else if (Name == 'S'){
    Stop();
  }

  else{
    Stop();
  }

}

void MotorController::RunMotors(){

  // PWM SPEED CONTROL

  if (PWMState == false){ 
    if (PWMtime * (1-Speed) < millis() - PWMLastTime){
      PWMState = true;
      PWMLastTime = millis();
      digitalWrite(M_LS, HIGH);
      digitalWrite(M_RS, HIGH);
    }
  }

  else{
    if (PWMtime * Speed < millis() - PWMLastTime){
      PWMState = false;
      PWMLastTime = millis();
      digitalWrite(M_LS, LOW);
      digitalWrite(M_RS, LOW);
    }
  }

  if (ActionLength < millis() - ActionStartTime){
    SetAction('S', 1000);
  }
}