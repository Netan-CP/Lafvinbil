// Motor

class MotorController{

private:

  float Speed = .1;

  int* M_LF;
  int* M_LB;
  int* M_RF;
  int* M_RB;
  int* M_LS;
  int* M_RS;

  int PWMtime = 10;
  int PWMLastTime = millis();
  bool PWMState = false;

  char CurrentAction = "S";
  int ActionLength = 1000;
  int ActionStartTime = 0;

  void Stop();

  void Forward();

  void Backward();

  void Turnleft();

  void Turnright();

public:
  
  MotorController(int, int, int, int, int, int);
  ~MotorController();

  void SetSpeed(float S){ Speed = S; }

  void SetAction(char* Name, int Time);

  void RunMotors();

  char getCurrentAction(){ return CurrentAction; }
    
};