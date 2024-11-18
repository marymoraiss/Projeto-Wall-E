# Motor de passo

O motor de passo utilizado é o SG90. É um motor de passo genérico bastante usado em projetos com microcontrolados devido a sua simplicidade. As suas especificações são o seguinte:

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

O controle do ângulo do motor de passo é feito por um sinal PWM. Ele deve ter um período fixo de 20ms (50Hz). A alrgura de pulso define o ângulo do motor. Para 1ms de largura de pulso, o âgulo correspondente do motor de passo é de 0º. Para 2ms de largura de pulso, o ângulo é de 180º. Essa relação entre largura de pulso e ângulo é linear. Portanto, pode ser definida pela seguinte equação.

$$\theta (t) = (t - 1ms) \cdot {180º \over 1ms}$$


## Conectores

- Vermelho: Alimentação positiva (3,0 até 7,2V)
- Marron: referência (GND)
- Laranja: Sinal de controle (PWM de 0 a 5V)

Como é necessário apenas um conector para controle, será necessário apenas um GPIO da Raspberry Pi para controlá-lo. O controle deve ser um sinal digital de 0 a 5V, portanto, será necessário converter o sinal da Raspberry Pi (3,3V).


# Validação dos motores

Para iniciarmos os projetos de movimentação do Wall-e, devemos validar o funcionamento de diversos componentes que o mesmo compõe, entre eles:

* Motores
* Drivers de acionamento
* Baterias


## Modelos dos motores

Os dois motores utilizados para as movimentar o Wall-e, são motores de corrente contínua comuns, os mesmos possuem velocidade e força necessárias para uma boa mobilidade. A imagem do modelo está abaixo:

![N|Walle](https://images.tcdn.com.br/img/img_prod/960515/micro_motor_ak380_ml24_9100c_261_1_0afbf1bb5c0c232fe3b26808873931e2.png)

Os outros 6 motores contidos no Wall-e servem para funções secundárias como: Mexer braço e virar cabeça. Estes por sua vez são feitos com servos motores SG90.

![Walle](img/micro_servo_motor.jpg)

Fonte: Autoria Própria

## Testes e Validações

Os testes para a validação do funcionamento dos motores, foram divididos em alguns aspectos, entre eles: 

- Identificar se o motor está funcionando corretamente sem carga
- Verificar o consumo de corrente sem e com carga
- Identificar um driver de acionamento, e testá-lo


### Motor DC

#### Identificando o Funcionamento do Motor:

![N|Walle](img/gif_motordc_rodando.gif)

Fonte: Autoria Própria


#### Verificar o Consumo de Corrente Sem/Com Carga:

Para o consumo de corrente do motor sem carga, foi utilizado uma fonte de bancada com corrente controlada, e assim foi possível identificá-la:

![N|Walle](img/teste_sem_carga_motordc.jpeg)

Fonte: Autoria Própria

Para identificar o consumo máximo de corrente com carga, é necessário segurar o motor para que ele tenha que se esforçar ao máximo, assim simulando um possível travamento das rodas.

![N|Walle](img/teste_carga_motordc.jpeg)

Os resultados podem ser observados na tabela abaixo:

| Motor DC | Corrente Máxima |
|  ------  |     ------      |
| S/ Carga |     170 mA      |
| C/ Carga |     580 mA      |


### Servo Motor 

#### Verificar o Consumo de Corrente Sem/Com Carga:

Para o consumo de corrente do servo motor sem carga, foi utilizado um arduino e a propria biblioteca do servo motor disponibilizada no site oficial, e assim foi possível identificá-la:

![N|Walle](img/teste_sem_carga_servomotor.jpeg)

Fonte: Autoria Própria

Para identificar o consumo máximo de corrente com carga, é necessário segurar o motor para que ele tenha que se esforçar ao máximo, assim simulando um possível travamento.

![N|Walle](img/teste_carga_servomotor.jpeg)

Fonte: Autoria Própria

Os resultados de corrente para o motor de passo está na tabela abaixo:

| Servo Motor | Corrente Máxima |
|   ------    |     ------      |
|  S/ Carga   |     270 mA      |
|  C/ Carga   |     1,85 A      |

Claro que os valores obtidos neste teste do servo motor, não será utilizado de maneira com máxima carga, vamos futuramente encontrar um valor nominal para a corrente, e desta forma faremos os cálculos para as baterias.

### Drivers de acionamento

Os drivers de acionamento são ferramentas essenciais para trabalhar com motores, elas são as partes que fazem o controle dos mesmos.

Portanto, foi pesando em utilizar os seguintes drivers:

Para os motores DC será utilizado um módulo driver motor ponte H baseado no chip L298N.

![N|Walle](img/ponte_h.png)

Fonte: Autoria Própria

Para os Servo Motores será utilizado o driver da biblioteca do arduino para o acionamento de controle dos motores.
  * https://www.arduino.cc/reference/en/libraries/servo/


### Testes e Validações

Os testes de validações de drivers, foram feitos a partir dos drivers citados acima.


#### Teste Driver Motor DC c/ L298N

![N|Walle](img/teste_driver_ponteh.jpeg)

Fonte: Autoria Própria


#### Teste Driver Servo Motor usando Biblioteca Servo.h.

![N|Walle](img/teste_driver_servomotor.png)

Fonte: Autoria Própria


Após as validações dos drivers e com os resultados obtidos de consumo de corrente dos motores, pode-se iniciar o processo de analise de consumo total de energia do circuito, para a construção dos módulos de bateria que serão utilizados.


---
Anterior: [Bateria](bateria.md) | Topo: [Desenvolvimento](README.md)
