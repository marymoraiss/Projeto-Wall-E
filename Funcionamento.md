# Diagrama de blocos para implementação do projeto:
Um diagrama funcional inicial do projeto foi elaborado, considerando os objetivos. Veja a figura abaixo. O usuário será uma pessoa controlando o robô a partir da interface web criada. 
![WhatsApp Image 2024-11-11 at 12 47 36](https://github.com/user-attachments/assets/e17f760a-ab92-4c37-a424-87a76b249d5c)

A interface gráfica do usuário será desenvolvida em Python (linguagem interpretada de alto nível) ou com qualquer ferramenta simples e bem documentada para criação de interfaces gráficas. 

A comunicação entre o usuário e o Wall-e será realizada via HTTP (rede). O protocolo HTTP (Hypertext Transfer Protocol) é usado para comunicação na web. Ele define como as mensagens são transmitidas e formatadas entre clientes (como navegadores) e servidores. O cliente faz uma solicitação (request) a um servidor, e o servidor responde (response) com dados, como uma página da web. HTTP é um protocolo sem estado, o que significa que cada troca é independente e não mantém informações.

A parte de movimentação dos servo-motores será implementada no microcontrolador ESP32 utilizando a linguagem C++, com o uso de PWM para acionamento. Para o motor CC, será empregada uma "ponte H" já existente no projeto, conforme mencionado.

Quanto à alimentação do projeto, uma fonte será usada para desenvolvimento e testes. Posteriormente, uma bateria será incorporada, visando proporcionar acessibilidade em locais sem uma fonte de energia próxima.

# Lista dos principais materiais e ferramentas do projeto:
- Carcaça do Wall-e impressa em 3D
- ESP32
- 8 Servo motores
- 2 Motores CC
- Computador (para gerenciar o Wall-e)
- Auto-falates caso haja tempo de implementar.
