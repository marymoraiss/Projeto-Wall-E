```c
// Motor ESQUERDO
#define motorEPin1 39 // Pino IN1 
#define motorEPin2 41 // Pino IN2 
#define enableEPin 40 // Pino PWM 

// Motor DIREITO
#define motorDPin1 38 // Pino IN1  
#define motorDPin2 35 // Pino IN2 
#define enableDPin 34 // Pino PWM

// PWM properties dc
const int freq = 30000; // Frequência do PWM (30 kHz)
const int resolution = 8; // Resolução de 8 bits (valores de 0 a 255)
int dutyCycle = 200; // Ciclo de trabalho inicial (velocidade)
const int pwmChanne0 = 0;
const int pwmChannel = 1;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

   //pinos dc
  pinMode(motorEPin1, OUTPUT);
  pinMode(motorEPin2, OUTPUT);
  pinMode(motorDPin1, OUTPUT);
  pinMode(motorDPin2, OUTPUT);

  // Configuração dos canais PWM
  ledcAttachChannel(enableEPin, freq, resolution, pwmChanne0); //pwm motor dc e
  ledcAttachChannel(enableDPin, freq, resolution, pwmChannel); //pwm motor dc d

  Serial.begin(115200);
  Serial.println("Testando Motores E e D...");
}
```
