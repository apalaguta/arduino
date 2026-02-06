#include <Servo.h>
#include <DHT.h>   
DHT dht(7, DHT11); 
int datchiki=3;
int servo=4;
int perv_kran=3;
int vtor_kran=2;
int temp=7;

int vlazn1=0;
int vlazn2=0;

bool otkrito=false;
bool kran1=false;
bool kran2=false;


Servo servo1;

void setup() {
  servo1.attach(10);
  servo1.write(0); 

  dht.begin();   

  pinMode(datchiki,OUTPUT);
  pinMode(servo,OUTPUT);
  pinMode(perv_kran,OUTPUT);
  pinMode(vtor_kran,OUTPUT);

  pinMode(temp,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);

}

void loop() {

  digitalWrite(datchiki, HIGH);
  int temp = dht.readTemperature();
    if(temp>25 and !otkrito){
        otkrito = true;
       for (int angle = 0; angle <= 90; angle++) {
        servo1.write(angle); 
        delay(20); 
    }
    }
    else if(temp<20 and otkrito){
      otkrito = false;
       for (int angle = 90; angle >= 0; angle--) {
      servo1.write(angle); // сообщаем микро серво угол поворота
      delay(20); 
       }
      otkrito=true;
    }



  vlazn1=analogRead(A2);
  if (vlazn1>500 and !kran1){
     digitalWrite(perv_kran, HIGH);
     kran1=false;
  }

  else if (vlazn1<300 and kran1){
    digitalWrite(perv_kran, LOW);
     kran1=true;
     }


vlazn2=analogRead(A3);
  if (vlazn2>500 and !kran2){
     digitalWrite(vtor_kran, HIGH);
     kran2=true;
  }
  else if (vlazn2<300 and kran2){
    digitalWrite(vtor_kran, LOW);
     kran2=false;
  }


  }
