//=============================================================\\
//DESN1000 - Rescue Robot
//Final Code
//Written by Aryaman Sakthivel (z5455785)
// ============================================================\\


//=============================================================\\
//Ultrasonic Sensors\\
//=============================================================\\

int Rtrig = 13;
int Recho = 12;
int Ltrig = 4;
int Lecho = 2;
int Ftrig = 9;
int Fecho = 8;

int RightSensor ()
{
  int distance;
  int RtimeMicro;

  digitalWrite(Rtrig,LOW);
  delayMicroseconds(2);
  digitalWrite(Rtrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Rtrig,LOW);

  RtimeMicro = pulseIn(Recho,HIGH);
  distance = RtimeMicro /29 /2;
  return (distance);

}

int LeftSensor ()
{
  int distance;
  int LtimeMicro;
  digitalWrite(Ltrig,LOW);
  delayMicroseconds(2);
  digitalWrite(Ltrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Ltrig,LOW);

  LtimeMicro = pulseIn(Lecho,HIGH);
  distance = LtimeMicro /29 /2;
  return (distance);
  
}

int FrontSensor ()
{
  int distance;
  int FtimeMicro;
  digitalWrite(Ftrig,LOW);
  delayMicroseconds(2);
  digitalWrite(Ftrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Ftrig,LOW);

  FtimeMicro = pulseIn(Fecho,HIGH);
  distance = FtimeMicro /29 /2;

  if (distance >= 6 and distance <=10) //Size of tennis ball is 6.7cm and distance from the ground to sensor is 13
  {
    Serial.println();
    Serial.print("Found...");
    Serial.println();
  }
}

//=============================================================\\
//Ultrasonic Sensors\\
//=============================================================\\

int RmotorLogicPin1 = 6;
int RmotorLogicPin2 = 7;
int LmotorLogicPin1 = 5;
int LmotorLogicPin2 = 3;
int FmotorLogicPin1 = 10;
int FmotorLogicPin2 = 11;
int pwmDutyCycle = 175;


char CurrentDir = '0';
static int motordata[4];

void initializing() 
{
  //Innitialise the digital output pins
  pinMode(RmotorLogicPin1, OUTPUT);
  pinMode(RmotorLogicPin2, OUTPUT);
  pinMode(LmotorLogicPin1, OUTPUT);
  pinMode(LmotorLogicPin2, OUTPUT);
  pinMode(FmotorLogicPin1, OUTPUT);
  pinMode(FmotorLogicPin2, OUTPUT);
  
  //Printing the motor configuration for wiring
  Serial.println("Initializing ...");
  Serial.print("Right Motor Pin 1 = ");
  Serial.println(RmotorLogicPin1);
  Serial.print("Right Motor Pin 2 = ");
  Serial.println(RmotorLogicPin2);
  Serial.print("Left Motor Pin 1 = ");
  Serial.println(LmotorLogicPin1);
  Serial.print("Left Motor Pin 2 = ");
  Serial.println(LmotorLogicPin2);
  Serial.println("Initialization Complete");
  Serial.print("Lift Mechanism Motor Pin 1 = ");
  Serial.println(FmotorLogicPin1);
  Serial.print("Lift Mechanism Motor Pin 2 = ");
  Serial.println(FmotorLogicPin2);
  Serial.println();
  Serial.println("Commands: ");

}

//Function: Recieve Command Byte
char recieveCommand()
{
  char command;
  //Check if there is anything in the buffer
  //if (Serial.available()>0)
  //{
    //Reads the first byte of the Serual Monitor and stores it 
    command = Serial.read();
  //}
  return command;
}

//Exit Subroutine
void exit()
{
	Serial.println();
  Serial.println("Exiting..");
  //while(true);
}

//Lift Up Subroutine:
void Lift()
{
  int liftpower = 95;

  delay(10);
  analogWrite (FmotorLogicPin1, 0);
  analogWrite (FmotorLogicPin2, liftpower);
  delay(190);
  analogWrite (FmotorLogicPin1, 0);
  analogWrite (FmotorLogicPin2, 0);
  
}

void Down()
{
  int liftpower = 90;

  delay(10);
  analogWrite (FmotorLogicPin1, liftpower);
  analogWrite (FmotorLogicPin2, 0);
  delay(215);
  analogWrite (FmotorLogicPin1, 0);
  analogWrite (FmotorLogicPin2, 0);
  
}

//Subroutine: Update Direction
int updateDirection (char command)
{
  //Switch Case for Incoming Byte
  switch (command)
  {
    case 'F':
    CurrentDir = 'F';
    motordata[0]=0;
    motordata[1]=pwmDutyCycle;
    motordata[2]=0;
    motordata[3]=pwmDutyCycle;
    break;

    case 'B':
    CurrentDir = 'B';
    motordata[0]=pwmDutyCycle;
    motordata[1]=0;
    motordata[2]=pwmDutyCycle;
    motordata[3]=0;
    break;

    case 'R':
    CurrentDir = 'R';
    motordata[0]=pwmDutyCycle;
    motordata[1]=0;
    motordata[2]=0;
    motordata[3]=pwmDutyCycle;
    break;

    case 'L':
    CurrentDir = 'L';
    motordata[0]=0;
    motordata[1]=pwmDutyCycle;
    motordata[2]=pwmDutyCycle;
    motordata[3]=0;
    break;

    case '0':
    CurrentDir = '0';
    Serial.println();
    Serial.println("Stopping");
    motordata[0]=0;
    motordata[1]=0;
    motordata[2]=0;
    motordata[3]=0;
    break;

    case 'H': //Climbing Stairs
    Serial.println();
    Serial.println("Hyper Drive Activated...");
    Serial.println();
    Serial.println("Robot is Ready to Climb the Stairs.");
    pwmDutyCycle = 255;
    break;

    case 'U':
    Serial.println();
    Serial.println("Lifting Up...");
    Lift();
    break;

    case 'D':
    Serial.println();
    Serial.println("Setting the Lift Mechanism Down...");
    Down();
    break;

    case 'P':
    Serial.println();
    Serial.println(pwmDutyCycle);
    break;

    case 'S':
    pwmDutyCycle = 175;
    break;

    case 'K':
    pwmDutyCycle =115;
    break;


    case 'X':
    //Calling the exit subroutine
    exit();
    break;
  }
}

//Subroutine: Update Speed 
void updateSpeed(char command)
{
  int speed = atoi(&command); //converts variable type from Chr to Int 
      
  //Check if Motor Speed is between 1-5
  if (speed >= 1 and speed <= 5)
  {
    pwmDutyCycle = pwmDutyCycle * speed/10;
    Serial.print("Speed : ");
    Serial.print(pwmDutyCycle); //Sets the new Speed of the Motors
    Serial.print("%");
  }

  else if (speed == 9 && pwmDutyCycle<=229)
  {
    pwmDutyCycle = pwmDutyCycle + (pwmDutyCycle * 0.10);
    Serial.println();
    Serial.println("Speed Increased by 10%"); //Sets the new Speed of the Motors
  }

  else if (speed == 8 && pwmDutyCycle>=56)
  {
    pwmDutyCycle = pwmDutyCycle - (pwmDutyCycle * 0.10);
    Serial.println();
    Serial.println("Speed Decreased by 10%"); //Sets the new Speed of the Motors
  }

  else
  {
    Serial.println("Invalid Duty Cycle...");
  }

  updateDirection(CurrentDir);
  setMotorPins(motordata);


}

//Subroutine: Set Motor Pins
void setMotorPins(int motordata[])
{
  //Writing the data from motordata to the Motor Pins
  analogWrite (RmotorLogicPin1, motordata[0]);
  analogWrite (RmotorLogicPin2, motordata[1]);
  analogWrite (LmotorLogicPin1, motordata[2]);
  analogWrite (LmotorLogicPin2, motordata[3]);
}


//========================================================\\
//Main\\
//========================================================\\

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Rescue Robot Team - 06");
  Serial.println();

  pinMode(Rtrig,OUTPUT);
  pinMode(Recho,INPUT);
  pinMode(Ltrig,OUTPUT);
  pinMode(Lecho,INPUT);
  pinMode(Ftrig,OUTPUT);
  pinMode(Fecho,INPUT);

  initializing(); 
}

void loop() {
  int Rdist;
  int Ldist;

  char command=0;
  command = recieveCommand();

  if (isDigit(command)>0 && command != '0')
  {
    //Call subroutine to update speed
    Serial.println();
    updateSpeed(command);
  }
  
  else
  {
    //Call function to update the direction
    updateDirection(command);
    //Call subroutine to set the motor pins
    setMotorPins(motordata);
  }

/*
  Rdist = RightSensor();
  Ldist = LeftSensor();
  

  Serial.println();
  Serial.print("\tRight Distance: ");
  Serial.print(Rdist);
  Serial.print("\tLeft Distance: ");
  Serial.print(Ldist);

*/
  FrontSensor();

  delay(20);
}
