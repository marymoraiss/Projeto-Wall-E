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

# Movimentação do Wall-e no modo teleoperado

No modo teleoperado, a movimentação do Wall-e será definida exclusivamente pelo operador (pessoa que controla o Wall-e). Ou seja, não há nenhum código controlando a movimentação do Wall-e de forma automática.


## Motores

O controle da velocidade dos motores será feito por meio de um PWM em software usando as GPIO da Raspberry Pi.

O duty cycle do PWM definirá a velocidade com que o Wall-e se movimentará e a forma como ele realizará as curvas. O eixo das rodas do Wall-e são fixos e não podem ser direcionados. Ou seja, não é possível que o Wall-e faça uma curva rotacionando suas rodas. Para girar o Wall-e, será necessário alterar a velocidade com que os motores das rodas giram. Girar a roda da esquerda mais rápido fará o Wall-e virar para a direita e vice-versa.

Já os motores de passo usados para mover os braços e cabeça do Wall-e, são controlados por meio da largura de pulso do PWM aplicado no terminal de controle. Também serão controlados usando os PWM em software da Raspberry Pi. Serão controlados apenas 3 dos 6 motores de passo. Os motores dos braços e do pescoço. Os movimentos dessas partes serão usados para notificar a identificação de lixo, como proposto na página ['Movimentação do Wall-e no modo autônomo'](autonomo.md).

Dependendo da exigência de processamento e comunicação da Raspberry Pi, ela pode não conseguir controlar o PWM do motor adequadamente. Assim, pode ser necessário terceirizar esse trabalho para um microcontrolador. Nessa situação, será usado uma esp32 para controlar os motores DC e de passo, enquanto a Raspberry Pi será responsável apenas pelo streaming de vídeo e enviar os comando para o esp32 por meio do wifi.


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

![Robo móvel](img/robo-movel.png)

Fonte: [Elvira Rafikova - Módulo Mobilidade](https://classes.elvirarafikova.com/rma/mobilidade/)

Substituindo os parâmetros, obtém-se a seguinte equação para velocidade angular:

$$\omega = {{p_d \cdot V_{max} \over 2L} - {p_e \cdot V_{max} \over 2L}}$$

Com as equações de velocidade linear e ângular do robô em função do duty cycle, pode-se montar um sistema linear. Com ele, é possível definir os duty cycle de cada roda.

$$\begin{cases} p_d + p_e = {2V \over V_{max}} \\\\ p_d - p_e = {2 \omega L \over V_{max}}\end{cases}$$


### Limitadores de corrente

Existe a possibilidade dos motores (tanto DC quanto de passo) travarem durante sua operação. Nessas condições, o consumo de corrente deles aumenta bastante. Para proteger a bateria nessas situações, deve-se limitar a correntes dos motores.

Será usado um circuito para limitar a corrente dos motores DC, e um para os motores de passo. É importante limitar eles de forma individual. Assim, se um dos motores travar e o limitador atuar, apenas o limitador associado a esse motor será acionado. Isso quer dizer que, se o motor de passo travar, o limitador do motor DC não será acionado e ele continua a operar normalmente.

Para limitar a corrente, será usado um circuito limitador de corrente com o LM317. É um circuito bastante conhecido e disponível, inclusive, nos datasheets desse componente. Veja a imagem abaixo:

![Limitador de corrente](img/limitador-corrente.png)

Fonte: datasheet LM317, Texas Instruments

A corrente de consumo dos motores é parâmetro medido e validado em laboratório. Os dados relacionados estão disponíveis na página ['Validação dos motores'](validacao-motores.md).

A corrente DC dos motores está na faixa de 170mA sem carga. Com carga está em 580mA. Como o Wall-e é leve e a lixeira acoplada será pequena, não será carregado muito peso. Assim, será considerado, inicialmente, uma corrente média de 300mA para cada motor. Esse valor será ajustado futuramente se o Wall-e necessitar de mais corrente. Por enquanto, será usado apenas para dimensionar o limitar de corrente.

Inicialmente, a corrente do motor DC será limitada em 300mA por cada motor. No total, 600mA. A resistência necessária para limitar a corrente será de:

$$I={{1,2V} \over R} \Rightarrow R={{1,2V} \over I} = {{1,2V} \over 600mA} = 2 \Omega$$

A potência mínima do resistor será de:

$$P = V \cdot I = 1.2V \cdot 600mA = 0,72W$$

Por segurança, será usado um resistor de no mínimo 1,5W.

Quanto a limitação de corrente dos motores de passo, eles consomem pouca corrente quando estão parados (na faixa dos 10mA). Ao mover, o consumo de corrente aumenta bastante, podendo chegar a mais de 1A caso um desses motores trave. Inicialmente, serão limitados em 600mA no total (todos os motores juntos). Dessa forma, pode-se usar um resistor igual ao do motor DC para os de passo. Futuramente, talvez esse valor deva ser ajustado.


### Driver ponte H

Para movimentar o Wall-e, será necessário, além de controlar a largura de pulso do PWM, controlar o sentido dos motores DC. Será usado um drive ponte H L298N. Ele permite inverter o sentido de rotação do motor invertendo o sentido da corrente que passa por ele.

A conexão padrão desse componente está ilustrada abaixo:

![Pinagem da ponte H](img/ponte-h-pinagem.png)

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


### Conversores de nível lógico

Como as saídas da Raspberry Pi são de 3.3V, é necessário usar um conversor de nível lógico para acionar circuitos digitais de 5V. O driver ponte H, assim como os motores de passo são acionados em 5V.

São necessárias 4 conexões digitais para a ponte H e 3 para o motor de passo. Assim, são necessárias 7 conexões no total. Cada conversor pode converter até 4 sinais digitais. Portanto, são necessários 2 conversores no total.

![Conversores lógicos](img/conversor-logico.png)


### Código para controlar os motores

O código será escrito em Python usando o módulo RPi.GPIO. Os PWM desse módulo são todos implementados em software (ainda não possuem suporte a PWM em hardware).

Em caso de o desempenho dessa implementação não for decente o bastante, os motores serão controlados usando um esp32 e a Raspberry Pi será responsável apenas pelo Streaming de vídeo. Isso alivia o trabalho sobre a Raspberry Pi.

Para o controle dos motores de passo, seu ângulo será variado lentamente. Evitar mudanças bruscas no ângulo do motor evita um consumo muito grande de correte por partes dele. Como informado anteriormente, esses motores podem possuir altas correntes se aplicado uma carga.


---
Anterior: [Comunicação do usuário com o Wall-e](comunicacao.md) | Topo: [Desenvolvimento](README.md) | Próximo: [Movimentação do Wall-e no modo autônomo](autonomo.md)

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
