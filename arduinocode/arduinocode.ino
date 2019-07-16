
// RX is digital pin 10 (connect to TX of other device)
//TX is digital pin 11 (connect to RX of other device)

#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);// RX, TX
const int triggerpin=10;//connect trigger pin of  ultrasonic sensor to 10th pin of arduino uno
const int echopin=11;//connect echo pin of  ultrasonic sensor to 11th pin of arduino uno
long duration;// establish variables for duration 
long distanceCm;// establish variables for distance
int val;// establish variables for reading received 2 byte data
int speeds;// establish variables for reading received 2 byte data
int m1f=2;
int m1b=4;
int m2f=5;
int m2b=7;
int m1=3;
int m2=6;
void setup()  
{
  pinMode(m1f, OUTPUT);//set mlf pin as output pin
  pinMode(m1b, OUTPUT);//set mlb pin as output pin
  pinMode(m2f, OUTPUT);//set m2f pin as output pin
  pinMode(m2b, OUTPUT);//set m2b pin as output pin
  pinMode(triggerpin,OUTPUT);//set trigger pin as output pin
  pinMode(echopin,INPUT);//sets echo pin as input pin 
  mySerial.begin(57600); // set the data rate for the SoftwareSerial port
}
void loop() // run over and over
{
  
 if (mySerial.available())//if number of bytes available to read greater than 0
  {
    val=mySerial.read();// read the incoming byte:
    speeds=mySerial.read();// read the incoming byte:
   
    digitalWrite(triggerpin,LOW);//sets trigger pin off for 2 microseconds
    delayMicroseconds(2);
    digitalWrite(triggerpin, HIGH);//sets trigger pin on for 10 microseconds
    delayMicroseconds(10);
    digitalWrite(triggerpin,LOW);//sets trigger pin off for 2 microseconds
    delayMicroseconds(2);
    duration = pulseIn(echopin, HIGH); //how much time the echo pin is high
    distanceCm = microsecondsToCentimeters(duration);// microsecondsToCentimeters function is called to convert the time into a distance
    

     if((val==2)&&(distanceCm>8.00))  //if received value is 2 and distance between robot and obstacle greater than 8cm then moveforward function is called,
    {                                 //we can change the limiting distance below which robot stops.                              
                                     //if we changed to if((val==2)&&(distanceCm>10.00)) then robot stops if obstacle is less than 10cm 
     moveforward(speeds,distanceCm);
     }
     else if((val==2)&&(distanceCm<8.00))// change here also 
     {                                   //if received value is 2 and distance between robot and obstacle lessthan 8cm then stops function is called
      stops(speeds,distanceCm);
     }
     else if(val==8)//if received value is 8 then movebackward function is called
     {
     movebackward(speeds,distanceCm);
     }
     else if(val==4)//if received value is 4 then leftturn function is called
     {
     leftturn(speeds,distanceCm);
     }
     else if(val==6)//if received value is 6 then rightturn function is called
     {
     rightturn(speeds,distanceCm);
     }
     else if(val==0)//if received value is 0 then stopped function is called
     {
     stopped(speeds,distanceCm);
     }
     else// if data is not received then prints "press buttons or say commands" below in the "robot status" label in the app
     {
     mySerial.print("press buttons or say commands");
    }
  }
  
}
    
 void moveforward(int x,long y)//x,y are passed from the function call
 {
    digitalWrite(m1f,LOW);
    digitalWrite(m2f,LOW);
    digitalWrite(m1b,HIGH);
    digitalWrite(m2b,HIGH);
    analogWrite(m1,x);
    analogWrite(m2,x);
    mySerial.println("Moving Forward");//prints "moving forward" below in the "robot status" label in the app
    mySerial.print("obstacle is at nearly");//prints "obstacle is at nearly" below in the "robot status" label in the app
    mySerial.print(y);//prints "y value" below in the "robot status" label in the app
    mySerial.print("cm");//prints "cm" below in the "robot status" label in the app
 }
   
 void movebackward(int x,long y)//x,y are passed from the function call
 {
    digitalWrite(m1f,HIGH);
    digitalWrite(m2f,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,LOW);
    analogWrite(m1, speeds);
    analogWrite(m2, speeds);
    mySerial.println("Moving Back");//prints "moving back" below in the "robot status" label in the app
    mySerial.print("obstacle is at nearly");//prints "obstacle is at nearly" below in the "robot status" label in the app
    mySerial.print(y);//prints "y value" below in the "robot status" label in the app
    mySerial.print("cm");//prints "cm" below in the "robot status" label in the app
 }
 void leftturn(int x,long y)//x,y are passed from the function call
 {
    digitalWrite(m1f,LOW);
    digitalWrite(m2f,LOW);
    digitalWrite(m1b,LOW);
    digitalWrite(m2b,HIGH);
    analogWrite(m1,0);
    analogWrite(m2,speeds);
    mySerial.println("Turning left");//prints "Turning left" below in the "robot status" label in the app
    mySerial.print("obstacle is at nearly");//prints "obstacle is at nearly" below in the "robot status" label in the app
    mySerial.print(y);//prints "y value" below in the "robot status" label in the app
    mySerial.print("cm");//prints "cm" below in the "robot status" label in the app
 }
 void rightturn(int x,long y)//x,y are passed from the function call
 {
   digitalWrite(m1f,LOW);
   digitalWrite(m2f,LOW);
   digitalWrite(m1b,HIGH);
   digitalWrite(m2b,LOW);
   analogWrite(m1,speeds);
   analogWrite(m2,0);
   mySerial.println("Turning Right");//prints "Turning right" below in the "robot status" label in the app
   mySerial.print("obstacle is at nearly");//prints "obstacle is at nearly" below in the "robot status" label in the app
   mySerial.print(y);//prints "y value" below in the "robot status" label in the app
   mySerial.print("cm");//prints "cm" below in the "robot status" label in the app
 }
   
 void stopped(int x,long y)//x,y are passed from the function call
 {
   digitalWrite(m1f,LOW);
   digitalWrite(m2f,LOW);
   digitalWrite(m1b,LOW);
   digitalWrite(m2b,LOW);
   analogWrite(m1, 0);
   analogWrite(m2,0);
   mySerial.println("Stopped!!");//prints "stopped!!" below in the "robot status" label in the app
   mySerial.print("obstacle is at nearly");//prints "obstacle is at nearly" below in the "robot status" label in the app
   mySerial.print(y);//prints "y value" below in the "robot status" label in the app
   mySerial.print("cm");//prints "cm" below in the "robot status" label in the app
 }
 void stops(int x,long y)//x,y are passed from the function call
 {
   digitalWrite(m1f,LOW);
   digitalWrite(m2f,LOW);
   digitalWrite(m1b,LOW);
   digitalWrite(m2b,LOW);
   analogWrite(m1, 0);
   analogWrite(m2,0); 
   mySerial.println("reached near obstacle");//prints "reached near obstacle" below in the "robot status" label in the app
   mySerial.print("obstacle is at nearly");//prints "obstacle is at nearly" below in the "robot status" label in the app
   mySerial.print(y);//prints "y value" below in the "robot status" label in the app
   mySerial.print("cm");//prints "cm" below in the "robot status" label in the app
 }
 long microsecondsToCentimeters(long microseconds)
 {
   // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2; 
 }

