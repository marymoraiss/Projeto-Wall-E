# Bibliotecas importadas

```
#include <WiFi.h>
#include <ESP32Servo.h>

```
- WiFi.h : Gerencia a conexão Wi-Fi do ESP32, permitindo criar um servidor HTTP.
- ESP32Servo.h : Facilita o controle de servomotores, essencial para os movimentos do robô.
---
# Definição dos Servos e Motores

```
Servo servo_olhoe;
Servo servo_olhod;

Servo servo_pescocos;
Servo servo_pescocom;
Servo servo_pescocoi;

Servo servo_bracoe;
Servo servo_bracod;
```

- Cada servo é instanciado para controle de diferentes partes do robô: olhos, pescoço e braços.
---

# Motores DC

```
// Motor ESQUERDO
#define motorEPin1 39 // Pino IN1 
#define motorEPin2 41 // Pino IN2 
#define enableEPin 40 // Pino PWM 

// Motor DIREITO
#define motorDPin1 38 // Pino IN1  
#define motorDPin2 35 // Pino IN2 
#define enableDPin 34 // Pino PWM
```
- Motores Esquerdo e Direito :
Pin1e Pin2controlam a direção (frente/trás).
enablePinajuste a velocidade usando PWM.

# Configuração de PWM
```
const int freq = 30000; // Frequência do PWM (30 kHz)
const int resolution = 8; // Resolução de 8 bits (valores de 0 a 255)
int dutyCycle = 200; // Ciclo de trabalho inicial (velocidade)
const int pwmChanne0 = 0;
const int pwmChannel = 1;
```
- PWM (Pulse Width Modulation) é usado para ajustar a velocidade dos motores. Os canais são configurados para os pinos de controle.
---

# Configuração do Wi-Fi
```
const char* ssid = "nome";
const char* password = "senha";
WiFiServer server(80);
```
- Conecte o ESP32 à rede Wi-Fi usando as credenciais confidenciais.
- Um servidor HTTP é criado na porta 80 para receber comandos do navegador.
---

# Configuração Inicial - setup()
```
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // LED para teste
  servo_olhoe.attach(pin_olhoe);
  // Configuração dos demais servos e motores...

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado.");
  Serial.println(WiFi.localIP());
  server.begin();
}
```
- Inicializa os servos, motores, e conecta o ESP32 à rede Wi-Fi.
- Exibe o endereço IP para acessar a interface web.
---

# Servidor HTTP e Interface Web
```
client.println("<button class='btn' onclick=\"location.href='/olhos'\">Ação Olhos</button>");
client.println("<button class='btn' onclick=\"location.href='/bracos'\">Ação Braços</button>");
```
- O ESP32 gera uma página HTML que inclui botões para controlar diferentes partes do robô.
- A página utiliza CSS para estilização e permite interatividade com setas direcionais.

# Comandos Baseados em URL
```
if (currentLine.endsWith("GET /olhos")) {
  Serial.println("Ação: Olhos");
  // Lógica para movimentar os olhos
}
if (currentLine.endsWith("GET /cima")) {
  Serial.println("Movimento: Para Cima");
  // Lógica para mover o robô para frente
}
```
Cada URL acessada pelo navegador executa uma ação específica no robô:
- olhos: Controla os olhos.
- bracos: Controla os braços.
- cima, baixo, esquerda, direita: Movimenta o robô em diferentes direções.

---

# Controle de Motores e Servos
Controle de Motores DC 
```
digitalWrite(motorEPin1, HIGH);
digitalWrite(motorEPin2, LOW);
ledcWrite(pwmChanne0, dutyCycle); // Ajusta a velocidade
```
- Define a direção do motor (frente ou ré) ajustando os pinos IN1 e IN2.
- Controla a velocidade usando PWM no pino enablePin.

Controle de Servos (EXEMPLO POIS AINDA VAI SERTESTADO)
```
servo_pescocoi.write(90); // Ajusta o ângulo do pescoço
delay(1000);
```
- Usa a biblioteca ESP32Servo para ajustar os ângulos de cada servo.
---

# Loop Principal (loop())
Estrutura de Controle
```
void loop() {
  WiFiClient client = server.available();
  if (client) {
    // Processa os comandos recebidos via HTTP
    if (currentLine.endsWith("GET /olhos")) {
      // Lógica para os olhos
    }
  }
}
```
- Escuta continuamente por conexões de clientes.
- Processa as requisições recebidas para executar ações específica

