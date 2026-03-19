#include <Servo.h>
#include <DHT.h>   
DHT dht(7, DHT11); 
#define datchiki 5
#define servo 6
#define perv_kran 4
#define vtor_kran 3
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
  servo1.attach(9);

  dht.begin();   

  pinMode(datchiki,OUTPUT);
  pinMode(servo,OUTPUT);
  pinMode(perv_kran,OUTPUT);
  pinMode(vtor_kran,OUTPUT);

  pinMode(temp,INPUT);
  pinMode(perv_vlaz1,INPUT);
  pinMode(perv_vlaz2,INPUT);

  digitalWrite(datchiki,HIGH);
digitalWrite(servo,HIGH);

digitalWrite(perv_kran,HIGH);
digitalWrite(vtor_kran,HIGH);

}

void loop() {

  digitalWrite(datchiki, LOW); // включаем питание датчиков
  delay(300);
  
  float t = dht.readTemperature(); // измеряем температуру
     Serial.println(t);   
  digitalWrite(servo,LOW); // подаем питание на сервопривод
    if(t>25 and !otkrito){
          Serial.println("-");
        otkrito = true;
       for (int pov = 0; pov <= 90; pov = pov + 5) {
        servo1.write(pov); 
        delay(30); 
    }
    }
    else if(t<20 and otkrito){
      otkrito = false;
          Serial.println("bbb");
       for (int pov = 90; pov >= 0; pov = pov - 5) {
      servo1.write(pov); 
      delay(30); 
       }
      otkrito=true;
    }
 delay(500);
digitalWrite(servo,HIGH); // выключаем питание на сервопривод

// измерение на первом датчике 
  vlazn1=analogRead(perv_vlaz1); 
    Serial.println(vlazn1);     
  if (vlazn1>400 and !kran1){
     digitalWrite(perv_kran, LOW);
     kran1=true;
  }
else if (vlazn1<200 and kran1){
    digitalWrite(perv_kran, HIGH);
     kran1=false;
}

// измерение влажности на  второом датчике
vlazn2=analogRead(perv_vlaz2);
  Serial.println(vlazn2);     
 if (vlazn2>400 and !kran2){
     digitalWrite(vtor_kran, LOW);
     kran2=true;
  }
  else if (vlazn2<200 and kran2){
    digitalWrite(vtor_kran, HIGH);
     kran2=false;
  }
digitalWrite(datchiki,HIGH);
peredacha(vlazn1,vlazn2,int(t));
delay(1000);
  }
// функция для передачи данных
  void peredacha(int vlazn_1, int vlazn_2, int temper){
    int procent1 = 0;
     int procent2 = 0;
    if (vlazn_1 < 200){
     int procent1 = 99;
    }
    else if (vlazn1 < 400){
     int procent1 = int((vlazn_1 - 200) / 4);
    }
   if (vlazn_2 < 200){
     int procent2 = 99;
    }
    else if (vlazn2 < 400){
     int procent2 = int((vlazn_2 - 200) / 4);
    }
   int dannie = temper * 10000 + procent1 * 100 + procent2 ; // подготовка данных для передачи
    Serial.println(dannie);   
  }
