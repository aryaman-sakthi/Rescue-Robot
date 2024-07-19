//=============================================================\\
//DESN1000 - Computer Technical Stream
//Lab 4 - Exercise 
//Written by Aryaman Sakthivel (z5455785)
// ============================================================\\

//Configuration of the motor pins
int RmotorLogicPin1 = 7;
int RmotorLogicPin2 = 6;
int LmotorLogicPin1 = 11;
int LmotorLogicPin2 = 10;
int pwmDutyCycle = 20;

//data about values of Motor Pins
static int motordata[4];


//Subroutine: Initialize Motor Pins
void initializing() 
{
  //Innitialise the digital output pins
  pinMode(RmotorLogicPin1, OUTPUT);
  pinMode(RmotorLogicPin2, OUTPUT);
  pinMode(LmotorLogicPin1, OUTPUT);
  pinMode(LmotorLogicPin2, OUTPUT);
  
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
  Serial.println();
  Serial.println("Commands: ");

}

//Function: Recieve Command Byte
char recieveCommand()
{
  char command;
  //Check if there is anything in the buffer
  if (Serial.available()>0)
  {
    //Reads the first byte of the Serual Monitor and stores it 
    command = Serial.read();
  }
  return command;
}

//Exit Subroutine
void exit()
{
	Serial.println("Exiting..");
  	while(true);
}

//Subroutine: Update Direction
int updateDirection (char command)
{
  //Switch Case for Incoming Byte
  switch (command)
  {
    case 'F':
    Serial.println("Current Direction: Forward");
    motordata[0]=0;
    motordata[1]=pwmDutyCycle;
    motordata[2]=0;
    motordata[3]=pwmDutyCycle;
    break;

    case 'B':
    Serial.println("Current Direction: Backward");
    motordata[0]=pwmDutyCycle;
    motordata[1]=0;
    motordata[2]=pwmDutyCycle;
    motordata[3]=0;
    break;

    case 'R':
    Serial.println("Current Direction: Right");
    motordata[0]=pwmDutyCycle;
    motordata[1]=0;
    motordata[2]=0;
    motordata[3]=pwmDutyCycle;
    break;

    case 'L':
    Serial.println("Current Direction: Left");
    motordata[0]=0;
    motordata[1]=pwmDutyCycle;
    motordata[2]=pwmDutyCycle;
    motordata[3]=0;
    break;

    case '0':
    Serial.println("Stopping");
    motordata[0]=0;
    motordata[1]=0;
    motordata[2]=0;
    motordata[3]=0;
    break;
    
    case 'x':
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
    pwmDutyCycle = speed*10;
    Serial.print("Speed : ");
    Serial.print(pwmDutyCycle); //Sets the new Speed of the Motors
    Serial.print("%");
  }
  else
  {
    Serial.println("Invalid Duty Cycle...");
  }

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

void setup() {
  //Initialize the serial communication
  Serial.begin(9600);

  Serial.println("Program : Motor Control");
  Serial.println();
  
  //Calling Initializing Function
  initializing();
  
}

void loop() 
{
  //Call function to recieve command
  char command;
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
  

  delay(10); //Small Delay for character to arrive
}
