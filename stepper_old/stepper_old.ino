//Globals
#define STEPPIN 11
#define DIRPIN 10
#define ENAPIN 9

const int STEPTIME = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(STEPPIN,OUTPUT);
  pinMode(DIRPIN,OUTPUT);
  pinMode(ENAPIN,OUTPUT);
  digitalWrite(ENAPIN,LOW);
}

int c = 1;
void loop() {
  int i;
  int steps = 200;
  if (c==1){
    rotateonce(steps,1);
    c = 0;
  }
  else{
    rotateonce(steps,0);
    c = 1;
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER

}

void rotateonce(int steps,int dir){
    digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
    digitalWrite(DIRPIN,dir);//SET DIRECTION 
    for(int i=0;i<steps;i++){
      Serial.println(i);
      digitalWrite(STEPPIN,HIGH);
      delay(10);
      digitalWrite(STEPPIN,LOW);
      delay(5);
    }  
}
void forward(int steps){
  int i;
  digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
  digitalWrite(DIRPIN,HIGH);//SET DIRECTION 
  for(i=0;i<steps;i++){
    Serial.println(i);
    digitalWrite(STEPPIN,HIGH);
    delay(STEPTIME);
    digitalWrite(STEPPIN,LOW);
    delay(STEPTIME);
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER
}

void reverse(int steps){
  int i;
  digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
  digitalWrite(DIRPIN,LOW);//SET DIRECTION 
  for(i=0;i<steps;i++){
    digitalWrite(STEPPIN,HIGH);
    delay(STEPTIME);
    digitalWrite(STEPPIN,LOW);
    delay(STEPTIME);
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER
}