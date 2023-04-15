// defines pins numbers

const int stepPin = 11;

const int dirPin  = 10;

// const int enPin  = 9;



int currentAngle = 0;

int angle = 0;

float stepPerAngle = 1.8; // full step = 1.8

int   numstep;



void setup() {

  Serial.begin(9600);

  // Sets the two pins as Outputs

  pinMode(stepPin,OUTPUT);

  pinMode(dirPin,OUTPUT);



  // pinMode(enPin,OUTPUT);

  // digitalWrite(enPin,LOW);

  digitalWrite(dirPin,HIGH);


}

int x = 0;

void loop() {

    int n;

    Serial.println(angle%360);

    if( currentAngle != angle ){

            digitalWrite(dirPin,LOW);

             n = angle - currentAngle;

            numstep = n / stepPerAngle;

            if( angle == 0){

               n = currentAngle;

            }


        for(int x = 0; x < numstep; x++) {

           digitalWrite(stepPin,HIGH);

           delayMicroseconds(1000);

           digitalWrite(stepPin,LOW);

           delayMicroseconds(1000);

        }
       currentAngle = angle;

    }



   delay(1000);

   angle+=45;

 

}