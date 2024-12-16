```
#include <ESP32Servo.h>

//criacao dos servos
Servo servo_olhoe;
Servo servo_olhod;

Servo servo_pescocos;
Servo servo_pescocom;
Servo servo_pescocoi;

Servo servo_bracoe;
Servo servo_bracod;

#define pin_olhoe 10
#define pin_olhod 11

#define pin_pescocos 12
#define pin_pescocom 13
#define pin_pescocoi 14

#define pin_bracoe 15
#define pin_bracod 16

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  //pinos dos servos
  servo_olhoe.attach(pin_olhoe);
  servo_olhod.attach(pin_olhod);
  servo_pescocos.attach(pin_pescocos);
  servo_pescocom.attach(pin_pescocom);
  servo_pescocoi.attach(pin_pescocoi);
  servo_bracoe.attach(pin_bracoe);
  servo_bracod.attach(pin_bracod);

  //pinos dc
  pinMode(motorEPin1, OUTPUT);
  pinMode(motorEPin2, OUTPUT);
  pinMode(motorDPin1, OUTPUT);
  pinMode(motorDPin2, OUTPUT);

  }
```
