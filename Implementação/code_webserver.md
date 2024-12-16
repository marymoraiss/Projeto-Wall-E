```c
#include <WiFi.h>

// Configuração do Wi-Fi
const char* ssid = "Maria";
const char* password = "marylinda";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

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
```
