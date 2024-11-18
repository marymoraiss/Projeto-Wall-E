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

