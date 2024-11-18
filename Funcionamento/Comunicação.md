# Comunicação entre o cliente e o Wall-e

A comunicação ocorrerá por meio de rede. Ou seja, tanto o usuario quanto o Wall-e deverão estar conectados a internet para poderem se comunicar. O Wall-e atuará como um servidor esperando o usuário se conectar a ele. O usuário estará atuando como um cliente tentando se conectar ao Wall-e. Quem inicia a conexão é o usuário. Apenas um usuário pode se conectar com o Wall-e por vez.

---

# Configuração do ESP32 como servidor ou cliente HTTP
O ESP32 pode funcionar tanto como um servidor quanto como um cliente HTTP.

Servidor HTTP no ESP32:

O ESP32 configura um ponto de acesso (Access Point) ou conecta-se a uma rede Wi-Fi existente.
Ele executa um servidor HTTP que pode lidar com requisições do tipo GET, POST ou outros métodos.
A interface web no navegador faz requisições HTTP (via um endereço IP) para o ESP32, que responde com dados ou realiza ações baseadas na requisição.

---

# Fluxo de comunicação entre a interface web e o ESP32
Caso 1: ESP32 como servidor HTTP
Interface web envia uma requisição:

O navegador ou aplicativo web (rodando em um dispositivo cliente) faz uma requisição HTTP para o ESP32.
Isso geralmente é feito através de uma URL, como http://<ip-do-esp32>/endpoint.
ESP32 processa a requisição:

Um framework como o ESPAsyncWebServer ou a biblioteca WebServer no Arduino IDE pode ser usado para gerenciar as requisições.
O ESP32 interpreta o método (GET, POST, etc.), os parâmetros da URL ou o corpo da requisição.
Resposta do ESP32:

O ESP32 envia uma resposta HTTP ao cliente, contendo um código de status (200, 404, etc.) e dados no formato adequado (geralmente texto, HTML ou JSON).
Interface web atualiza os dados:

A interface web exibe os dados recebidos ou reflete alterações baseadas na resposta do ESP32

---

# Interface Web

o Designin da interface a principio será como a imagem abaixo:

![‘](https://github.com/user-attachments/assets/523d2ef2-c862-43a9-a1d5-8c1aeb8f112d)

Fonte: Autoria Propria

Na imagem podemos observar como sera a movimentação da esteira do robô para locomoção.

