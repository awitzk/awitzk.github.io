#include <Servo.h>
Servo myservo;  // create servo object to control a servo
Servo mydialservo;// twelve servo objects can be created on most boards


//pinMode(7,OUTPUT);    // Relay Signal Pin
//digitalWrite(7,HIGH);
   
int pos = 0;    // variable to store the servo position
float locklength = 0;

int increment = 18;  //deg per five minutes
int degincrement = increment/(5*60)*10; //deg per ten seconds should be around 0.6 

float pos2 = 180-increment ; // set servo to ON pos
float dial = 180-increment ; // goal of postion2k servo
  

const int plusbuttonPin = 4; //sets button pin 2
const int minusbuttonPin = 2; //sets button pin 2

int waittime = 0; //time between the last button press and the start of the lock

int plusbuttonState = 0;         // variable for reading the pushbutton status
int minusbuttonState = 0;         // variable for reading the pushbutton status

void setup() {

  Serial.begin(9600); // for printing
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  mydialservo.attach(10);  

 
  
  //pinMode(5, OUTPUT);
  //digitalWrite(5, HIGH);
  
  pinMode(plusbuttonPin, INPUT); // initialize the pushbutton pin as an input:
  pinMode(minusbuttonPin, INPUT); // initialize the pushbutton pin as an input:
  
  myservo.write(pos); //sets servo to strart position
  mydialservo.write(pos2);
  while (waittime <= 30000 ){
    plusbuttonState = digitalRead(plusbuttonPin); //read button states
    minusbuttonState = digitalRead(minusbuttonPin);
    
      if(plusbuttonState == 1 || minusbuttonState == 1){
        waittime = 0;  //if button is pressed, wait time restarts
          if(plusbuttonState == 1 && locklength < 2700000){    //plus button adds 5 sec
            locklength = locklength + 300000; //20g for 5 min increment
            dial = dial - increment;

            for (pos2; pos2 > dial; pos2 -= 1) { // goes from 0 degrees to 180 degree in steps of 1 degree
            mydialservo.write(pos2);              // tell servo to go to position in variable 'pos'
            delay(10);                       // waits 15ms for the servo to reach the position
            
            }
               
          }                           // this delay gets replaced by the dial servo moving
          if(minusbuttonState == 1 && locklength > 0){    // minus button substracts 5 sec
            locklength -= 300000;
              dial = dial + increment;

            for (pos2; pos2 < dial; pos2 += 1) { // goes from 0 degrees to 180 degree in steps of 1 degree
            mydialservo.write(pos2);              // tell servo to go to position in variable 'pos'
            delay(10);
            }
          }
        Serial.print("Locklength:");
        Serial.print(locklength);         //int locklength is too small
        Serial.println();
          Serial.print("pos2 ");
        Serial.print(pos2);         //int locklength is too small
        Serial.println();
      }    
      
      else {
      delay(100);
      waittime = waittime+100;
        }
    
  }
  
  
  
}
void loop() {
 
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (locklength; locklength >= 0; locklength -= 10000) { // goes from 180 degrees to 0 degrees
    pos2 = pos2 + 0.6;
    mydialservo.write(pos2); 
     Serial.print("angle: ");
        Serial.print(pos2);         //int locklength is too small
        Serial.println();// tell servo to go to position in variable 'pos'
        Serial.print("length: ");
        Serial.print(locklength);         
        Serial.println();
    delay(10000);                       
  }
   //use countdown with servo instead 1sec is 0.059 at 45 min per 160
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  mydialservo.write(180);
  //use mosfet to auto turnoff
  //digitalWrite(7, LOW);
  while(1){}
}
