// C++ code
//
#include<Servo.h>

#define motorf1p 2
#define motorf1n 3
#define motorf2p 4
#define motorf2n 5
#define motorb1p 6
#define motorb1n 7
#define motorb2p 8
#define motorb2n 9

#define triggerpin 10
#define echopin 11
#define servopin 12 


Servo myservo;
void setup()
{
  Serial.begin(9600);
  myservo.attach(servopin);

  pinMode(motorf1p, OUTPUT);
  pinMode(motorf1n, OUTPUT);
  pinMode(motorf2p, OUTPUT);
  pinMode(motorf2n, OUTPUT);
  pinMode(motorb1p, OUTPUT);
  pinMode(motorb1n, OUTPUT);
  pinMode(motorb2p, OUTPUT);
  pinMode(motorb2n, OUTPUT);
  
}

int reverse(int state){
  if (state == 0) return 1;
  else return 0;
}

int power;
void move(String direction, int posmax){
  if (direction == "right") power = 1;
  else power = 0;

  //different values for rotation of TASLA's direction
  if (direction != "center" ){ 
    digitalWrite(motorf1p , power);          //forward
    digitalWrite(motorf1n , reverse(power)); //backward
    digitalWrite(motorf2p , power);          //backward
    digitalWrite(motorf2n , reverse(power)); //forward
    digitalWrite(motorb1p , power);          //forward
    digitalWrite(motorb1n , reverse(power)); //backward
    digitalWrite(motorb2p , reverse(power)); //backward
    digitalWrite(motorb2n , power);          //forward
    delay(posmax * 20);
  }

  power = 0;
  //all forward to move TASLA forward
  digitalWrite(motorf1p , reverse(power));
  digitalWrite(motorf1n , power);
  digitalWrite(motorf2p , power);
  digitalWrite(motorf2n , reverse(power));
  digitalWrite(motorb1p , power);
  digitalWrite(motorb1n , reverse(power));
  digitalWrite(motorb2p , power);
  digitalWrite(motorb2n , reverse(power));
  delay(500);
  
  
  digitalWrite(motorf1p , 0);
  digitalWrite(motorf1n , 0);
  digitalWrite(motorf2p , 0);
  digitalWrite(motorf2n , 0);

  Serial.println("Motor Move ends");
}

long dist(int trig, int echo){
  pinMode(trig, OUTPUT);
  digitalWrite(trig,0);
  delayMicroseconds(2);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  pinMode(echo,INPUT);
  return pulseIn(echo,HIGH); 
}

unsigned int range = 0;
int pos = 90;
int i=1;
int check = -1;
int check1 = -1;
int rangemax = 0;
int posmax = 90;
String direction;

void loop()
{
  range = 0.01723 * dist(triggerpin,echopin);

  if (rangemax < range and range<200){
    rangemax = range;
    if (pos < 90) direction = "right";
    else if (pos > 90) direction = "left";
    else direction = "center";
    posmax = abs(90-pos);

    Serial.print("ANGLE = ");
    Serial.print(posmax);
    Serial.print("  DIR = ");
    Serial.print(direction);
    Serial.print("  RANGEMAX = ");
    Serial.println(range);
  }

  if (range<100) {
    check = 1;
    digitalWrite(motorb1p , 0);
    digitalWrite(motorb1n , 0);
    digitalWrite(motorb2p , 0);
    digitalWrite(motorb2n , 0);
  }
  else check = 0;
  Serial.println(range);
  
  if (check == 1) check1 = 1;

  if (check1 == 1){
    if(i == 1){
        pos-=10;
        myservo.write(pos);
        pos = myservo.read();
        if (pos == 30) i=0;
      }
      else if (i == 0){
        pos+=10;
        myservo.write(pos);
        pos = myservo.read();
        if (pos == 150) i = 2;
      }       
      else{
        pos-=10;
        myservo.write(pos);
        pos = myservo.read();
        if (pos == 90) {
          i = 1;
          Serial.println("Motor Move start");
          move(direction,posmax);
          check1 = 0;
          rangemax = 0;
          posmax = 0;
        }
    }
    Serial.print("pos ");
    Serial.println(pos); 
  }
  else if (check1 == 0){
    if (pos>90){
      pos-=10;
      myservo.write(pos);
      pos = myservo.read();
    }
    else if (pos<90){
      pos+=10;
      myservo.write(pos);
      pos = myservo.read();
    }
  }
  
      
    
  delay(100); // Wait for 100 millisecond(s)
}