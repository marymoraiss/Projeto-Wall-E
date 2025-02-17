#include <WiFi.h>
#include <ESP32Servo.h>

// Definição do SSID e senha do ponto de acesso
const char* ssid = "ESP32_AP";  // Nome da rede Wi-Fi
const char* password = "12345678"; // Senha da rede

WiFiServer sv(80); //Cria um servidor na porta 80

// Variavel para guardar o HTTP 
String header;

// Definição dos servos motores
Servo servo_olhoe;
Servo servo_olhod;

Servo servo_pescocos;
Servo servo_pescocom;
Servo servo_pescocoi;

Servo servo_bracoe;
Servo servo_bracod;

#define pin_olhoe 2
#define pin_olhod 11

#define pin_pescocos 12
#define pin_pescocom 13
#define pin_pescocoi 14

#define pin_bracoe 15
#define pin_bracod 16

// Motor A
#define PINO_IN1 2
#define PINO_IN2 4 

//Motor B
#define PINO_IN3 5
#define PINO_IN4 18 

void setup() {
  Serial.begin(115200);

  // Configura os pinos de controle como saída
  pinMode(PINO_IN1, OUTPUT);  // Define o pino IN1 como saída
  pinMode(PINO_IN2, OUTPUT);  // Define o pino IN2 como saída
  pinMode(PINO_IN3, OUTPUT);  // Define o pino IN3 como saída
  pinMode(PINO_IN4, OUTPUT);  // Define o pino IN4 como saída

  pinMode(23, OUTPUT);  //Define a porta 23 como saída
  delay(10);  //Atraso de 10 milissegundos

   // Conecta ao Wi-Fi com o SSID e senha
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  sv.begin();

  // Inicialização dos servos
  servo_olhoe.attach(pin_olhoe);
  servo_olhod.attach(pin_olhod);
  servo_pescocos.attach(pin_pescocos);
  servo_pescocom.attach(pin_pescocom);
  servo_pescocoi.attach(pin_pescocoi);
  servo_bracoe.attach(pin_bracoe);
  servo_bracod.attach(pin_bracod);
}

void loop() {

 WiFiClient client = sv.available(); //Cria o objeto cliente

   if (client) {                             // Se um novo cliente conecta,
    Serial.println("New Client.");
    String currentLine = "";                // Faz uma string para guardar informação vindas do cliente
    while (client.connected()) {            // Loop enquando o cliente estiver conectado
      if (client.available()) {             // Se houver bytes para ler do cliente
        char c = client.read();             // Lê o byte
        Serial.write(c);                    // Printa o byte no monitor serial
        header += c;
        if (c == '\n') {
          // Fim do http 
      
          if (currentLine.length() == 0) {
            // Responder ao cliente
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
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

	  //OLHOS
    if (currentLine.endsWith("GET /olhos")) {
    Serial.println("Acao: Olhos");
          
    client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo Olhos...</h1></body></html>");
        }
        }


	  //BRACOS
    if (currentLine.endsWith("GET /bracos")) {
  	//ESQUERDO
	  for (int pos = 90; pos <= 180; pos += 1) { // sweep from 0 degrees to 180 degrees
		servo_bracoe.write(pos);
		delay(10);             // waits 20ms for the servo to reach the position
	}
  	for (int pos = 180; pos >= 90; pos -= 1) { // sweep from 0 degrees to 180 degrees
		servo_bracoe.write(pos);
		delay(10);             // waits 20ms for the servo to reach the position
	}
    for (int pos = 90; pos >= 60; pos -= 1) { // sweep from 0 degrees to 180 degrees
		servo_bracoe.write(pos);
		delay(10);             // waits 20ms for the servo to reach the position
	}
  	for (int pos = 60; pos <= 90; pos += 1) { // sweep from 0 degrees to 180 degrees
		servo_bracoe.write(pos);
		delay(10);             // waits 20ms for the servo to reach the position
}
  
 	//DIREITO
    	
    for (int pos = 90; pos >= 0; pos -= 1) { // sweep from 0 degrees to 180 degrees
		servo_bracod.write(pos);
		delay(10);             // waits 20ms for the servo to reach the position
 }
    for (int pos = 0; pos <= 90; pos += 1) { // sweep from 0 degrees to 180 degrees
		servo_bracod.write(pos);
		delay(10);             // waits 20ms for the servo to reach the position
 }
    client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo Bracos...</h1></body></html>");
}
        

	//PESCOCO
    if (currentLine.endsWith("GET /pescoco")) {
    Serial.println("Acao: ativa Pescoco");

   //GIRA A CABECA
   for (int pos = 90; pos <= 180; pos += 1) { // sweep from 0 degrees to 180 degrees
	 servo_pescocos.write(pos);
	 delay(10);             // waits 20ms for the servo to reach the position
 }
   for (int pos = 180; pos >= 90; pos -= 1) { // sweep from 0 degrees to 180 degrees
	 servo_pescocos.write(pos);
	 delay(10);             // waits 20ms for the servo to reach the position
 }
   for (int pos = 90; pos >= 60; pos -= 1) { // sweep from 0 degrees to 180 degrees
	 servo_pescocos.write(pos);
	 delay(10);             // waits 20ms for the servo to reach the position
 }
   for (int pos = 60; pos <= 90; pos += 1) { // sweep from 0 degrees to 180 degrees
	 servo_pescocos.write(pos);
	 delay(10);             // waits 20ms for the servo to reach the position
 }      
  client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo Pescoco...</h1></body></html>");
}


  //PRA FRENTE
        
  if (currentLine.endsWith("GET /cima")) {
  Serial.println("Movimento: Para Frente");
  int valor_pwm = 0;  // Variável para armazenar o valor PWM (0-255)

  // Aumenta a velocidade gradualmente de 0% a 100% no sentido horário
  for (valor_pwm = 0; valor_pwm < 256; valor_pwm++) {
  analogWrite(PINO_IN1, valor_pwm);  // Aplica o valor PWM no pino IN1
  analogWrite(PINO_IN3, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de aumentar a velocidade
  }
  // Diminui a velocidade gradualmente de 100% a 0% no sentido horário
  for (valor_pwm = 255; valor_pwm >= 0; valor_pwm--) {
  analogWrite(PINO_IN1, valor_pwm);  // Reduz o valor PWM no pino IN1
  analogWrite(PINO_IN3, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de diminuir mais a velocidade
  }
   client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo para Frente...</h1></body></html>");
}

  //PRA TRAS

  if (currentLine.endsWith("GET /baixo")) {
  Serial.println("Movimento: Para Baixo");
  int valor_pwm = 0;
  // Aumenta a velocidade gradualmente de 0% a 100% no sentido anti-horário
  for (valor_pwm = 0; valor_pwm < 256; valor_pwm++) {
  analogWrite(PINO_IN2, valor_pwm);  // Aplica o valor PWM no pino IN2
  analogWrite(PINO_IN4, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de aumentar a velocidade
  }
 
  // Diminui a velocidade gradualmente de 100% a 0% no sentido anti-horário
  for (valor_pwm = 255; valor_pwm >= 0; valor_pwm--) {
  analogWrite(PINO_IN2, valor_pwm);  // Reduz o valor PWM no pino IN2
  analogWrite(PINO_IN4, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de diminuir mais a velocidade
  } 
  client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo para Baixo...</h1></body></html>");
}


	//ESQUERDA
  if (currentLine.endsWith("GET /esquerda")) {
  Serial.println("Movimento: Para Esquerda");
  int valor_pwm = 0;  // Variável para armazenar o valor PWM (0-255)

  // Aumenta a velocidade gradualmente de 0% a 100% no sentido horário
  for (valor_pwm = 0; valor_pwm < 256; valor_pwm++) {
  analogWrite(PINO_IN1, valor_pwm);  // Aplica o valor PWM no pino IN1
  analogWrite(PINO_IN4, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de aumentar a velocidade
  }
  // Diminui a velocidade gradualmente de 100% a 0% no sentido horário
  for (valor_pwm = 255; valor_pwm >= 0; valor_pwm--) {
  analogWrite(PINO_IN1, valor_pwm);  // Reduz o valor PWM no pino IN1
  analogWrite(PINO_IN4, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de diminuir mais a velocidade
  }

  client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo para Esquerda...</h1></body></html>");
}

	//DIREITA
  if (currentLine.endsWith("GET /direita")) {
  Serial.println("Movimento: Para Direita");
  int valor_pwm = 0;
  // Aumenta a velocidade gradualmente de 0% a 100% no sentido anti-horário
  for (valor_pwm = 0; valor_pwm < 256; valor_pwm++) {
  analogWrite(PINO_IN2, valor_pwm);  // Aplica o valor PWM no pino IN2
  analogWrite(PINO_IN3, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de aumentar a velocidade
  }
 
  // Diminui a velocidade gradualmente de 100% a 0% no sentido anti-horário
  for (valor_pwm = 255; valor_pwm >= 0; valor_pwm--) {
  analogWrite(PINO_IN2, valor_pwm);  // Reduz o valor PWM no pino IN2
  analogWrite(PINO_IN3, valor_pwm);  // Aplica o valor PWM no pino IN1
  delay(50);  // Espera 100 ms antes de diminuir mais a velocidade
  } 

  client.println("<html><head><meta http-equiv='refresh' content='1;url=/' /></head><body><h1>Movendo para Direita...</h1></body></html>");
  }
 }
}
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

