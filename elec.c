/*
ELEC1100 Your Lab#06 & Project Template
To program the car tracking the white line on a dark mat
Group No. (number on your project box): 89
Group Member 1 (name & SID): Tara Relan 20716928
Group Member 2 (name & SID): Sandeepti Singh 2067923509
*/
 
const int pinB_Sensor = A1;
const int pinR_Sensor = A3;
const int pinM_Sensor = A4;
const int pinL_Sensor = A5;
 
const int pinL_PWM = 9;
const int pinL_DIR = 10;
 
const int pinR_PWM = 11;
const int pinR_DIR = 12;
 
int bumperSensor = 1;
int leftSensor = 1;
int middleSensor = 1;
int rightSensor = 1;
 
int countWall = 0;
int countWallBack = 0;
int countSplit = 0; 
int countSharpTurn = 0;
int speedControl = 0; 
void setup()
{
   pinMode(pinB_Sensor, INPUT);
   pinMode(pinR_Sensor, INPUT);
   pinMode(pinM_Sensor, INPUT);
   pinMode(pinL_Sensor, INPUT);
 
   pinMode(pinL_PWM, OUTPUT);
   pinMode(pinL_DIR, OUTPUT);

   pinMode(pinR_PWM, OUTPUT);
   pinMode(pinR_DIR, OUTPUT);
 
   analogWrite(pinL_PWM, 0);
   digitalWrite(pinL_DIR, HIGH);
 
   analogWrite(pinR_PWM, 0);
   digitalWrite(pinR_DIR, HIGH);
}
 
void loop()
{
   bumperSensor = digitalRead(pinB_Sensor);
   rightSensor = digitalRead(pinR_Sensor);
   middleSensor = digitalRead(pinM_Sensor);
   leftSensor = digitalRead(pinL_Sensor);
 
   // Stationary car at the beggining
   if (bumperSensor && countWall == 0)
   {
       analogWrite(pinR_PWM, 0);
       analogWrite(pinL_PWM, 0);
       digitalWrite(pinR_DIR, HIGH);
       digitalWrite(pinL_DIR, HIGH);
   }
   // Start when the bumper sensor is triggered 
   if (!bumperSensor && !leftSensor && !rightSensor && countWall == 0 && countSplit == 0)
   {
       analogWrite(pinR_PWM, 350);
       analogWrite(pinL_PWM, 350);
       digitalWrite(pinR_DIR, HIGH);
       digitalWrite(pinL_DIR, HIGH);
       countWall += 1;
   }
   if (countWall > 0 && countWallBack == 0)
   {
       //dealing with two left splits and one right split
       if (middleSensor && !leftSensor && !rightSensor)
       {

           //two left splits
           if (countSplit < 2)
           {
               analogWrite(pinR_PWM, 350);
               analogWrite(pinL_PWM, 350);
               digitalWrite(pinR_DIR, HIGH);
               digitalWrite(pinL_DIR, LOW);
               countSplit += 1;
               if (countSplit == 1)
               {
                   delay(250);
               }
 
               else if (countSplit == 2)
               {
                   delay(250);
               }
           }

           //right split 
           else if (countSplit == 2)
           {
               analogWrite(pinR_PWM, 350);
               analogWrite(pinL_PWM, 350);
               digitalWrite(pinR_DIR, LOW);
               digitalWrite(pinL_DIR, HIGH);
               countSplit += 1;
               delay(250);
           }

            //the same condition is encountered at the first sharp turn so accomodating that 
           else if (countSplit == 3)
           {
               analogWrite(pinR_PWM, 350);
               analogWrite(pinL_PWM, 350);
               digitalWrite(pinR_DIR, HIGH);
               digitalWrite(pinL_DIR, LOW);
               countSplit += 1;
               delay(250);
               }
       }

       if (speedControl == 0){
       // Both black, go straight
       if (leftSensor && rightSensor)
       {
           analogWrite(pinR_PWM, 350);
           analogWrite(pinL_PWM, 350);
           digitalWrite(pinR_DIR, HIGH);
           digitalWrite(pinL_DIR, HIGH);
       }
       // Left white, turn left
       if (!leftSensor && rightSensor)
       {
           analogWrite(pinR_PWM, 350);
           analogWrite(pinL_PWM, 350);
           digitalWrite(pinR_DIR, HIGH);
           digitalWrite(pinL_DIR, LOW);
       }
       // Right white, turn right
       if (leftSensor && !rightSensor)
       {
           analogWrite(pinR_PWM, 350);
           analogWrite(pinL_PWM, 350);
           digitalWrite(pinR_DIR, LOW);
           digitalWrite(pinL_DIR, HIGH);
       }
       }

        if(countSplit > 2){
          speedControl == 1; 
        }
        
        //reducing speed for the sharp right angled turns 
       if(speedControl > 0) {
          if (leftSensor && rightSensor)
           {
               analogWrite(pinR_PWM, 150);
               analogWrite(pinL_PWM, 150);
               digitalWrite(pinR_DIR, HIGH);
               digitalWrite(pinL_DIR, HIGH);
           }
           // Left white, turn left
           if (!leftSensor && rightSensor)
           {
               analogWrite(pinR_PWM, 150);
               analogWrite(pinL_PWM, 150);
               digitalWrite(pinR_DIR, HIGH);
               digitalWrite(pinL_DIR, LOW);
           }
           // Right white, turn right
           if (leftSensor && !rightSensor)
           {
               analogWrite(pinR_PWM, 150);
               analogWrite(pinL_PWM, 150);
               digitalWrite(pinR_DIR, LOW);
               digitalWrite(pinL_DIR, HIGH);
           }
       }
   }
   if (!bumperSensor && countWallBack == 0 && countWall == 1 && countSplit > 1)
   {
       countWallBack += 1;
   }
   if (countWallBack)
   {
       if (leftSensor && rightSensor)
       {
           analogWrite(pinR_PWM, 350);
           analogWrite(pinL_PWM, 350);
           digitalWrite(pinR_DIR, LOW);
           digitalWrite(pinL_DIR, LOW);
           delay(350);
           analogWrite(pinR_PWM, 0);
           analogWrite(pinL_PWM, 0);
           digitalWrite(pinR_DIR, HIGH);
           digitalWrite(pinL_DIR, LOW);
           
       }
       
       /*if (!middleSensor && leftSensor && !rightSensor)
       {
           analogWrite(pinR_PWM, 0);
           analogWrite(pinL_PWM, 0);
       }
       */
   }
 /*
   if (!leftSensor &&!rightSensor &&!middleSensor && countSplit > 1 && countWall == 1 && countSharpTurn <= 0)
   {
       //making it turn left for now may need to be changed to right?
       analogWrite(pinR_PWM, 50);
       analogWrite(pinL_PWM, 50);
       digitalWrite(pinR_DIR, HIGH);
       digitalWrite(pinL_DIR, LOW);
       countSharpTurn ++;
   }

    if (leftSensor &&!rightSensor &&!middleSensor && countSplit > 1 && countWall == 1 && countSharpTurn <= 0)
   {
       //making it turn left for now may need to be changed to right?
       analogWrite(pinR_PWM, 50);
       analogWrite(pinL_PWM, 50);
       digitalWrite(pinR_DIR, HIGH);
       digitalWrite(pinL_DIR, LOW);
       countSharpTurn ++;
   }
*/
   if (!leftSensor && !rightSensor &&!middleSensor && countSplit > 1 && countWall == 1 && countSharpTurn == 0)
   {
       //making it turn left for now may need to be changed to right?
       analogWrite(pinR_PWM, 150);
       analogWrite(pinL_PWM, 150);
       digitalWrite(pinR_DIR, HIGH);
       digitalWrite(pinL_DIR, LOW);
       countSharpTurn ++;
       delay(250)
   }

  /*
  if (!leftSensor && !rightSensor && middleSensor && countSplit > 1 && countWall == 1 && countSharpTurn <= 0)
   {
       //making it turn left for now may need to be changed to right?
       analogWrite(pinR_PWM, 50);
       analogWrite(pinL_PWM, 50);
       digitalWrite(pinR_DIR, HIGH);
       digitalWrite(pinL_DIR, LOW);
       countSharpTurn ++;
   }
   */

   
}
 


