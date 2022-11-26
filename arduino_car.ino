#include <Servo.h> 

const int LeftMotorForward = 5;
const int LeftMotorBackward = 6;
const int RightMotorBackward = 9;
const int RightMotorForward = 10;
const int trigpin = 3;
const int echopin = 13;
const int buzzer = 2;
const int laserPin = 12;
int duration;
int distance;
Servo myservo;

void move_forwards()                          //move forward(all motors rotate in forward direction).
{
   digitalWrite(RightMotorForward, HIGH);
   digitalWrite(RightMotorBackward, LOW);
   digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
}

void move_backwards()                         //move reverse(all motors rotate in backward direction).
{
   digitalWrite(RightMotorForward, LOW);
   digitalWrite(RightMotorBackward, HIGH);
   digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
}

void turn_right()                             //move right(right side motors rotate in reverse direction, left side motors rotate in forward direction).
{
   digitalWrite(RightMotorForward, HIGH);
   digitalWrite(RightMotorBackward, LOW);
   digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
}

void turn_left()                              //move left(right side motors rotate in forward direction, left side motors rotate in reverse direction).
{
   digitalWrite(RightMotorForward, LOW);
   digitalWrite(RightMotorBackward, HIGH);
   digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
}

void halt()                                   //STOP(stop all motors).
{
  digitalWrite(RightMotorForward, LOW);
   digitalWrite(RightMotorBackward, LOW);
   digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, LOW);
}

void bluetooth_control(char bluetooth_input)  //control the car by sending F,B,L,R and S letters via bluetooth.
{
    if(t == 'F'){         
      move_forwards();
    }
    if(t == 'B'){         
      move_backwards();
    }
    if(t == 'L'){         
      turn_left();
    }
    if(t == 'R'){         
      turn_right();
    }
    if(t == 'S'){         
      halt();
    } 
}

int get_distance()                    //calculate the distance using ultrasonic sensor.
{
   digitalWrite(trigpin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigpin, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(trigpin, LOW);
   duration = pulseIn(echopin, HIGH);
   distance = (duration*.0343)/2;
   return distance;
}

int look_right()                      //rotate the ultrasonic sensor mounted on the servo motor and check the distance at 170 degree angle to the right.
{
  myservo.write(10);
  delay(500);
  int right_path = get_distance();
  myservo.write(90);
  return right_path;
}

int look_left()                       //rotate the ultrasonic sensor mounted on the servo motor and check the distance at 170 degree angle to the left.
{
  myservo.write(170);
  delay(500);
  int left_path = get_distance();
  myservo.write(90);
  return left_path;
}

void self_control()
{
  move_forwards();                    //move forward as long as the distance measured is greater than 30cm.
  int distance = get_distance();
  myservo.write(90);
  if(distance <= 30)                  //stop the car for 300ms if the distance measured is less than 30cm.
  {
    halt();
    delay(300);
    int dist_right = look_right();                        //measure the distance at the right side.
    int dist_left = look_left();                          //measure the distance at the left side.
    if(dist_right > dist_left && dist_right >= 30)        //if the distance to the right greater than that to the left, move to the right side.
    {
      turn_right();
    }
    else if(dist_right < dist_left && dist_left >= 30)    //if the distance to the left greater than that to the right, move to the left side.
    {
      turn_left();
    }
    else
    {
      move_backwards();                                   //if the distance in both sides(right and left) less than 30cm, move backward then repeat the process.
      if(dist_right > dist_left && dist_right >= 30)      
    {
      turn_right();
    }
    else if(dist_right < dist_left && dist_left >= 30)
    {
      turn_left();
    }
    }
    delay(430);
  }
}

void setup()
{
  myservo.attach(11);                     //servo motor attached to pin 11.
   pinMode(trigpin, OUTPUT);              //trigger pin of the ultrasonic sensor .
  pinMode(echopin, INPUT);                //echo pin of the ultrasonic sensor.
  pinMode(RightMotorForward, OUTPUT);     //forward motor to the right.
  pinMode(LeftMotorForward, OUTPUT);      //forward motor to the left.
  pinMode(LeftMotorBackward, OUTPUT);     //backward motor to the left.
  pinMode(RightMotorBackward, OUTPUT);    //backward motor to the right.
  pinMode(laserPin, OUTPUT);              //laser module pin.
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()){                 //read the letter from the bluetooth module.
    t = Serial.read();
  }
  bluetooth_control(t);                   //the car is controlled by the bluetooth by default.
  if(t == 'W')                            //letter W puts the car in self driving mode and avoids obstacles.
    self_control();
  if(t == 'w')                            //letter w exits the self driving mode.
    halt();
  if(t == 'V')                            //letter V turns on the horn.
    tone(buzzer,300);
  if(t == 'v')                            //letter v turns off the horn
    noTone(buzzer);
  if(t == 'U')                            //letter U turns the laser light on.
    digitalWrite(laserPin, HIGH);
  if(t == 'u')                            //letter u turns the laser light off.
    digitalWrite(laserPin, LOW);
}
