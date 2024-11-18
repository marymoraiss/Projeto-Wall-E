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

## Modelos dos motores

Os dois motores utilizados para as movimentar o Wall-e, são motores de corrente contínua comuns, os mesmos possuem velocidade e força necessárias para uma boa mobilidade. A imagem do modelo está abaixo:

![N|Walle](https://images.tcdn.com.br/img/img_prod/960515/micro_motor_ak380_ml24_9100c_261_1_0afbf1bb5c0c232fe3b26808873931e2.png)

Os outros 6 motores contidos no Wall-e servem para funções secundárias como: Mexer braço e virar cabeça. Estes por sua vez são feitos com servos motores SG90.

![image](https://github.com/user-attachments/assets/95c43641-1b9a-41bc-906e-73e05664bd60)


Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)

## Testes e Validações

Os testes para a validação do funcionamento dos motores, foram divididos em alguns aspectos, entre eles: 

- Identificar se o motor está funcionando corretamente sem carga
- Verificar o consumo de corrente sem e com carga
- Identificar um driver de acionamento, e testá-lo


### Motor DC

#### Identificando o Funcionamento do Motor:

![image](https://github.com/user-attachments/assets/ab7dcc7e-a561-46ba-ae5e-7015f4352a24)


Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)


#### Verificar o Consumo de Corrente Sem/Com Carga:

Para o consumo de corrente do motor sem carga, foi utilizado uma fonte de bancada com corrente controlada, e assim foi possível identificá-la:

![image](https://github.com/user-attachments/assets/ad802188-a63a-4c2c-a2a8-760c50052507)


Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)


Para identificar o consumo máximo de corrente com carga, é necessário segurar o motor para que ele tenha que se esforçar ao máximo, assim simulando um possível travamento das rodas.

![image](https://github.com/user-attachments/assets/ea04a9ed-4bb8-432d-82a6-707a740bf4c1)

Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)

Os resultados podem ser observados na tabela abaixo:

| Motor DC | Corrente Máxima |
|  ------  |     ------      |
| S/ Carga |     170 mA      |
| C/ Carga |     580 mA      |


### Servo Motor 

#### Verificar o Consumo de Corrente Sem/Com Carga:

Para o consumo de corrente do servo motor sem carga, foi utilizado um arduino e a propria biblioteca do servo motor disponibilizada no site oficial, e assim foi possível identificá-la:

![image](https://github.com/user-attachments/assets/6c3e06d3-0ca2-4818-b0df-11ab51fe9039)

Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)

Para identificar o consumo máximo de corrente com carga, é necessário segurar o motor para que ele tenha que se esforçar ao máximo, assim simulando um possível travamento.

![image](https://github.com/user-attachments/assets/e9356f2f-5c93-4098-9de2-83810a530962)


Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)

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

![image](https://github.com/user-attachments/assets/48614b1e-409e-443a-8b55-a1e73e981ded)

Fonte: [Equipe Lucas e Lucas](https://github.com/MatheusPinto/PI_IFSC_2023_02/blob/main/equipe_LuLu/design/validacao-motores.md)

Para os Servo Motores será utilizado o driver da biblioteca do arduino para o acionamento de controle dos motores.
  * https://www.arduino.cc/reference/en/libraries/servo/


### Testes e Validações

Os testes de validações de drivers, foram feitos a partir dos drivers citados acima.

