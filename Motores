# Motor de passo

O motor de passo utilizado é o SG90. É um motor de passo genérico bastante usado em projetos com microcontroladores devido a sua simplicidade. As suas especificações são o seguinte:

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

O controle do ângulo do motor de passo é feito por um sinal PWM. Ele deve ser um período fixo de 20ms (50Hz). A largura de pulso define o ângulo do motor. Para 1ms de largura de pulso, o ângulo correspondente do motor de passo é de 0º. Para 2ms de largura de pulso, o ângulo é de 180º. Essa relação entre largura de pulso e ângulo é linear. Portanto, pode ser definida pela seguinte equação.

$$\theta (t) = (t - 1ms) \cdot {180º \over 1ms}$$


## Conectores

- Vermelho: Alimentação positiva (3,0 até 7,2V)
- Marrom: referência (GND)
- Laranja: Sinal de controle (PWM de 0 a 5V)

Como é necessário apenas um conector para controle, será necessário apenas um GPIO da Raspberry Pi para controlá-lo. O controle deve ser um sinal digital de 0 a 5V, portanto, será necessário converter o sinal da Raspberry Pi (3,3V).
