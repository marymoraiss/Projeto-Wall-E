Codigo completo: [Uploading tes#include <WiFi.h>

//biblioteca servos motores
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

// Configuração do Wi-Fi
const char* ssid = "Maria";
const char* password = "marylinda";

WiFiServer server(80);

// Pinos para as ações
int LED = 2; // Apenas como exemplo, você pode substituir pelos pinos que controlam os olhos, braços, etc.

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

  // Configuração dos canais PWM
  ledcAttachChannel(enableEPin, freq, resolution, pwmChanne0); //pwm motor dc e
  ledcAttachChannel(enableDPin, freq, resolution, pwmChannel); //pwm motor dc d

  Serial.begin(115200);
  Serial.println("Testando Motores E e D...");

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado.");
  Serial.print("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo Cliente Conectado.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Enviar a página HTML para o cliente
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTML com o design desejado
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; text-align: center; background: linear-gradient(to bottom, #cce7e8, #f5f7fa); }");
            client.println(".btn { padding: 15px 30px; margin: 10px; border: 2px solid black; border-radius: 10px; background-color: #e0f7fa; font-size: 16px; cursor: pointer; }");
            client.println(".btn:hover { background-color: #b2ebf2; }");
            client.println(".arrow { width: 50px; height: 50px; display: inline-block; margin: 10px; background-color: #b2ebf2; clip-path: polygon(50% 0%, 100% 100%, 0% 100%); cursor: pointer; }");
            client.println(".up { transform: rotate(0deg); }");
            client.println(".down { transform: rotate(180deg); }");
            client.println(".left { transform: rotate(-90deg); }");
            client.println(".right { transform: rotate(90deg); }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Controle do Robo</h1>");

            client.println("<button class='btn' onclick=\"location.href='/olhos'\">Acao Olhos</button><br>");
            client.println("<button class='btn' onclick=\"location.href='/bracos'\">Acao Bracos</button><br>");
            client.println("<button class='btn' onclick=\"location.href='/pescoco'\">Acao Pescoco</button><br><br>");

            client.println("<div>");
            client.println("<div class='arrow up' onclick=\"location.href='/cima'\"></div><br>");
            client.println("<div class='arrow left' onclick=\"location.href='/esquerda'\"></div>");
            client.println("<div class='arrow' style='background-color: transparent;'></div>");
            client.println("<div class='arrow right' onclick=\"location.href='/direita'\"></div><br>");
            client.println("<div class='arrow down' onclick=\"location.href='/baixo'\"></div>");
            client.println("</div>");

            client.println("</body>");
            client.println("</html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Comandos baseados nas URLs
        if (currentLine.endsWith("GET /olhos")) {
          Serial.println("Acao: Olhos");
          // Adicione aqui a lógica para "Ação Olhos"

        }
        if (currentLine.endsWith("GET /bracos")) {
          Serial.println("Acao: Bracos");
          // Adicione aqui a lógica para "Ação Braços"
        }
        if (currentLine.endsWith("GET /pescoco")) {
          Serial.println("Acao: ativa Pescoco");
          // Adicione aqui a lógica para "Ação Pescoço"
          servo_pescocoi.write(90);
          delay(1000);
          //servo_pescocom.write(90);
          //delay(1000);

        }
        if (currentLine.endsWith("GET /cima")) {
          Serial.println("Movimento: Para Cima");
          // Adicione aqui a lógica para mover para cima
        }
        if (currentLine.endsWith("GET /baixo")) {
          Serial.println("Movimento: Para Baixo");
          // Adicione aqui a lógica para mover para baixo
        }
        if (currentLine.endsWith("GET /esquerda")) {
          Serial.println("Movimento: Para Esquerda");
          // Adicione aqui a lógica para mover para esquerda
        }
        if (currentLine.endsWith("GET /direita")) {
          Serial.println("Movimento: Para Direita");
          // Adicione aqui a lógica para mover para direita
        }
      }
    }
    client.stop();
    Serial.println("Cliente Desconectado.");
  }
}
te_server1_copy_20241216165903.ino…]()


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

