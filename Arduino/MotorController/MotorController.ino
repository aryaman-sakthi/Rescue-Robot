//=============================================================\\
//DESN1000 - Computer Technical Stream
//Lab 3 - Exercise 
//Written by Aryaman Sakthivel (z5455785)
// ============================================================\\

//Configuration of the motor pins
int RmotorLogicPin1 = 10;
int RmotorLogicPin2 = 11;
int LmotorLogicPin1 = 6;
int LmotorLogicPin2 = 5;
int pwmDutyCycle = 100;

//Incoming Byte from the Serial Monitor
char direction = 0;

void initializing()  //Function for initializing
{
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

void setup()
{
  //Initialize the serial communication
  Serial.begin(9600);

  Serial.println("Program : Motor Control");
  Serial.println();
  
  // Initialise the digital output pins
  pinMode(RmotorLogicPin1, OUTPUT);
  pinMode(RmotorLogicPin2, OUTPUT);
  pinMode(LmotorLogicPin1, OUTPUT);
  pinMode(LmotorLogicPin2, OUTPUT);

  //Calling Initializing Function
  initializing();

}

void loop()
{
  
  //Check if there is anything in the buffer
  if (Serial.available()>0)
  {
    //Reads the first byte of the Serual Monitor and stores it 
    char direction = Serial.read();
    Serial.println();
    
    //Incoming Byte "f" -- move Forward
    if (direction =='f')
    {
      Serial.println("Forward");
      analogWrite (RmotorLogicPin1, 0);
      analogWrite (RmotorLogicPin2, pwmDutyCycle);
      analogWrite (LmotorLogicPin1, 0);
      analogWrite (LmotorLogicPin2, pwmDutyCycle);
    }

    //Incoming Byte "b" -- move Backward 
    else if (direction =='b')
    {
      Serial.println("Backward");
      analogWrite (RmotorLogicPin1, pwmDutyCycle);
      analogWrite (RmotorLogicPin2, 0);
      analogWrite (LmotorLogicPin1, pwmDutyCycle);
      analogWrite (LmotorLogicPin2, 0);
    }

    //Incoming Byte "r" -- turn Right
    else if (direction =='r')
    {
      Serial.println("Right");
      analogWrite (RmotorLogicPin1, pwmDutyCycle);
      analogWrite (RmotorLogicPin2, 0);
      analogWrite (LmotorLogicPin1, 0);
      analogWrite (LmotorLogicPin2, pwmDutyCycle);
    }

    //Incoming Byte "l" -- turn Left
    else if (direction == 'l')
    {
      Serial.println("Left");
      analogWrite (RmotorLogicPin1, 0);
      analogWrite (RmotorLogicPin2, pwmDutyCycle);
      analogWrite (LmotorLogicPin1, pwmDutyCycle);
      analogWrite (LmotorLogicPin2, 0);
    }

    //Incoming Byte "0" -- Stop
    else if (direction == '0')
    {
      Serial.println("Stop");
      analogWrite (RmotorLogicPin1, 0);
      analogWrite (RmotorLogicPin2, 0);
      analogWrite (LmotorLogicPin1, 0);
      analogWrite (LmotorLogicPin2, 0);
    }

    //Incoming Byte used to control Speed
    else if (isDigit(direction) > 0) 
    {
      int speed = atoi(&direction); //converts variable type from Chr to Int 
      
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
  }
  delay(10); //Small Delay for character to arrive 
}
