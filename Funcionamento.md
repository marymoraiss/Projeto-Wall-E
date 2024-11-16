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

# Servo Motor

O servo motor utilizado é o SG90. É um motor de passo genérico bastante usado em projetos com microcontroladores devido a sua simplicidade. As suas especificações são o seguinte:

|      Especificação      |                Valor                |
|          :---:          |                :---:                |
|       Alimentação       |             3,0 - 7,2V              |
|     Rotação máxima      |              180 graus              |
|    Velocidade máxima    |  0,12 seg/60Graus (4,8V) sem carga  |
|      Torque máximo      | 1,2 kg.cm (4,8V) e 1,6 kg.cm (6,0V) |
| Temperatura de operação |             -30C ~ +60C             |
|        Dimensões        |           32 x 30 x 12mm            |
|          Peso           |                 9g                  |

Adaptado de: [Eletrogate - Micro Servo 9g SG90](https://www.eletrogate.com/micro-servo-9g-sg90-towerpro)

O ângulo do motor de passo é controlado por um sinal PWM com um período fixo de 20 ms (50 Hz). A largura do pulso determina o ângulo do motor. Quando a largura do pulso é de 1 ms, o ângulo correspondente é 0°. Já para uma largura de pulso de 2 ms, o ângulo é 180°. Essa relação entre a largura do pulso e o ângulo é linear e pode ser expressa pela seguinte equação:

$$\theta (t) = (t - 1ms) \cdot {180º \over 1ms}$$


## Conectores

- Vermelho: Alimentação positiva (3,0 até 7,2V)
- Marrom: referência (GND)
- Laranja: Sinal de controle (PWM de 0 a 5V)

Como é necessário apenas um conector para controle, será utilizado apenas um GPIO do ESP32 para realizar essa tarefa. O controle exige um sinal digital de 0 a 5V; assim, será necessário implementar um circuito de conversão de nível lógico para ajustar o sinal do ESP32 (3,3V) para 5V.
