#include <Servo.h>
#include <DHT.h>   
DHT dht(7, DHT11); 
#define datchiki 4
#define servo 5
#define perv_kran 3
#define vtor_kran 2
#define  temp 7

#define perv_vlaz1 A2
#define perv_vlaz2 A3

int vlazn1 = 0;
int vlazn2 = 0;

bool otkrito = false;
bool kran1 = false;
bool kran2 = false;


Servo servo1;


void setup() {
  Serial.begin(9600);
  servo1.attach(10);
  servo1.write(0); 

  dht.begin();   

  pinMode(datchiki,OUTPUT);
  pinMode(servo,OUTPUT);
  pinMode(perv_kran,OUTPUT);
  pinMode(vtor_kran,OUTPUT);

  pinMode(temp,INPUT);
  pinMode(perv_vlaz1,INPUT);
  pinMode(perv_vlaz2,INPUT);

}

void loop() {

  digitalWrite(datchiki, HIGH);

  float t = dht.readTemperature();
  digitalWrite(servo,HIGH);
    if(t>25 and !otkrito){
        otkrito = true;
       for (int pov = 0; pov <= 90; pov++) {
        servo1.write(pov); 
        delay(20); 
    }
    }
    else if(t<20 and otkrito){
      otkrito = false;
       for (int pov = 90; pov >= 0; pov--) {
      servo1.write(pov); 
      delay(20); 
       }
      otkrito=true;
    }



  vlazn1=analogRead(perv_vlaz1);
    Serial.print(vlazn1);     
  if (vlazn1>500 and !kran1){
     digitalWrite(perv_kran, HIGH);
     kran1=false;
  }

  else if (vlazn1<300 and kran1){
    digitalWrite(perv_kran, LOW);
     kran1=true;
     }


vlazn2=analogRead(perv_vlaz2);
  Serial.print(vlazn2);     
 if (vlazn2>500 and !kran2){
     digitalWrite(vtor_kran, HIGH);
     kran2=true;
  }
  else if (vlazn2<300 and kran2){
    digitalWrite(vtor_kran, LOW);
     kran2=false;
  }


  }