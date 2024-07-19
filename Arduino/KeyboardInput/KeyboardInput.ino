//=============================================================\\
//DESN1000 - Computer Technical Stream
//Exercise 1
//Written by Aryaman Sakthivel (z5455785)
// ============================================================\\

//Program to read a line of text and display it one character at a time


char incomingByte; //Global Variable 'incomingByte'

void setup()
{
  //Initialize the serial communications 
  Serial.begin(9600);
  
  //Heading Displayed
  Serial.println("Char-by-Char Text Display: \n");
    
}

void loop()
{
  //Checks if there is anything in the buffer	
  if(Serial.available())
  {
    //Reads the first byte of the Serial Monitor and stores it in
    incomingByte = Serial.read();
    
    //Prints the character stored in incomingByte
    Serial.println(incomingByte);
  }
}
