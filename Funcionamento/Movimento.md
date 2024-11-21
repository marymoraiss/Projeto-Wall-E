# Diagrama para implementação do projeto:
Um diagrama funcional inicial do projeto foi elaborado, considerando os objetivos. Veja a figura abaixo. O usuário será uma pessoa controlando o robô a partir da interface web criada. 
![WhatsApp Image 2024-11-11 at 12 47 36](https://github.com/user-attachments/assets/e17f760a-ab92-4c37-a424-87a76b249d5c)

Fonte: Autoria própria.

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


# Movimentação do Wall-e

No modo teleoperado, a movimentação do Wall-e será definida exclusivamente pelo operador (pessoa que controla o Wall-e). Ou seja, não há nenhum código controlando a movimentação do Wall-e de forma automática.


## ESP32

O ESP32 é um microcontrolador poderoso e versátil, desenvolvido pela Espressif Systems. Ele integra conectividade Wi-Fi e Bluetooth, sendo ideal para projetos IoT. Possui um processador dual-core, memória flash, GPIOs configuráveis, além de suporte a diversos protocolos. É amplamente utilizado devido ao baixo custo, eficiência energética e facilidade de programação, especialmente com plataformas como Arduino e MicroPython.

![image](https://github.com/user-attachments/assets/f4dd7293-6a00-4130-bf97-b2651627d773)

Fonte:https://portal.vidadesilicio.com.br/conhecendo-o-esp32/ 

## Motor CC

O controle da velocidade dos motores será feito por meio de um PWM em software usando ESP32.

O duty cycle do PWM definirá a velocidade com que o Wall-e se movimentará e a forma como ele realizará as curvas. O eixo das rodas do Wall-e são fixos e não podem ser direcionados. Ou seja, não é possível que o Wall-e faça uma curva rotacionando suas rodas. Para girar o Wall-e, será necessário alterar a velocidade com que os motores das rodas giram. Girar a roda da esquerda mais rápido fará o Wall-e virar para a direita e vice-versa.

### Cinemática

A definição do duty cycle dos motores será feita com o auxílio da análise cinemática inversa do robô móvel. O material de base dessa análise está disponínel no seguinte vídeo no Youtube ['Cinemática de Robôs Móveis - Parte 1: Definições e Modelo de Robô Diferencial'](https://www.youtube.com/watch?v=yR5aHQm1p3U).

A velocidade linear é dada por:

$$v_{x} = {{\varphi_d \cdot r \over 2} + {\varphi_e \cdot r \over 2}}$$

Pd: velocidade angular da roda direita

Pe: velocidade angular da roda esquerda

r: raio da roda

Ou seja, é a média da velocidade linear de cada roda (direita e esquerda), podendo ser escrita da seguinte forma considerando o duty cycle dos motores:

$$V = {{p_d \cdot V_{max} \over 2} + {p_e \cdot V_{max} \over 2}}$$

pd: duty cycle do motor direito

pe: duty cycle do motor esquerdo

Vmax: velocidade linear máxima do motor

Quanto a velocidade ângular:

$$\omega = {{\varphi_d \cdot r \over 2L} - {\varphi_e \cdot r \over 2L}}$$

L é o raio do robô móvel (do centro até a roda), conforme a imagem abaixo:

![image](https://github.com/user-attachments/assets/cffd3848-c2e6-42a9-accb-a71a9c55cbc2)


Fonte: [Elvira Rafikova - Módulo Mobilidade](https://classes.elvirarafikova.com/rma/mobilidade/)

Substituindo os parâmetros, obtém-se a seguinte equação para velocidade angular:

$$\omega = {{p_d \cdot V_{max} \over 2L} - {p_e \cdot V_{max} \over 2L}}$$

Com as equações de velocidade linear e ângular do robô em função do duty cycle, pode-se montar um sistema linear. Com ele, é possível definir os duty cycle de cada roda.

$$\begin{cases} p_d + p_e = {2V \over V_{max}} \\\\ p_d - p_e = {2 \omega L \over V_{max}}\end{cases}$$

### Driver ponte H

Para movimentar o Wall-e, será necessário, além de controlar a largura de pulso do PWM, controlar o sentido dos motores DC. Será usado um drive ponte H L298N. Ele permite inverter o sentido de rotação do motor invertendo o sentido da corrente que passa por ele.

A conexão padrão desse componente está ilustrada abaixo:

![image](https://github.com/user-attachments/assets/38477193-471d-492d-bfa8-3df5bf1fcf74)


Fonte: [Makehero - Motor DC com Driver Ponte H L298N](https://www.makerhero.com/blog/motor-dc-arduino-ponte-h-l298n/)

- 6-35V: alimentação da ponte H.
- GND: Tensão de referência da ponte H.
- 5V: Saída de 5V disponibilizada pela ponte H (possui regulador interno). Caso a alimentação de 6-35V não seja usada e o jumper ATIVA 5V esteja ativo, o conector de 5V fornece uma alimentação de 5V com limitação de até 200mA. No caso de o jumper ATIVA 5V estiver desconectado, a porta 5V atua como uma alimentação de 5V para os motores.
- ATIVA MA e ATIVA MB: Jumpers que habilitam os motores DC. Remover os jumpers desabilita eles.

Nesse projeto, os motores necessitarão de mais de 5V de alimentação, que estará ligada ao conector de 6-35V; portanto, o jumper ATIVA 5V estará ativo (não será usada alimentação de 5V para os motores).

Os dois motores serão usados; então, os jumpers ATIVA MA e ATIVA MB estarão ativos.

O controle do sentido de rotação é dado pelas entradas de 4 pinos do driver (marcada de azul na imagem anterior). O sentido dos motores depende dos níveis lógicos dessas entradas conforme a seguinte tabela da verdade:

| Comportamento do motor A | IN1   | IN2   |
| :---:                    | :---: | :---: |
| Horário                  | 5V    | GND   |
| Anti-horário             | GND   | 5V    |
| Ponto morto              | GND   | GND   |
| Freio                    | 5V    | 5V    |

Fonte: [Makehero - Motor DC com Driver Ponte H L298N](https://www.makerhero.com/blog/motor-dc-arduino-ponte-h-l298n/)

A tabela do motor B é análoga a do motor A.

O acionamento desses pinos será feito pelos GPIO da Raspberry Pi.

Há uma proteção interna de chaveamento que impede o curto-circuito da ponte H em caso de acionamento de IN1 e IN2 ao mesmo tempo.

Os limitadores de corrente dos motores DC serão postos na alimentação do driver ponte H.

![Captura de tela de 2024-11-18 12-16-22](https://github.com/user-attachments/assets/7628694d-b6b0-4a45-939e-0285f94bc38c)

Fonte: Autoria própria.
_ _ _

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

![image](https://github.com/user-attachments/assets/beba083e-6427-4b54-8bd2-a5cc3a48c6a9)

Fonte: Autoria própria.

## Conectores

- Vermelho: Alimentação positiva (3,0 até 7,2V)
- Marrom: referência (GND)
- Laranja: Sinal de controle (PWM de 0 a 5V)

Como é necessário apenas um conector para controle, será utilizado apenas um GPIO do ESP32 para realizar essa tarefa. O controle exige um sinal digital de 0 a 5V; assim, será necessário implementar um circuito de conversão de nível lógico para ajustar o sinal do ESP32 (3,3V) para 5V.
