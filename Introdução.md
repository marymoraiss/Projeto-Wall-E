# Movimentação do Robô Wall-E
A Internet das Coisas (IoT) oferece soluções inovadoras para integrar dispositivos à internet, gestão inteligente e eficiência energética. Este projeto pretende demonstrar o controle remoto de um robô, usando uma interface web para simular interações práticas entre a tecnologia IoT e o mundo físico.

No Laboratório de Pesquisa Avançada em Eletrônica (LPAE) do Instituto Federal de Santa Catarina (IFSC), campus Florianópolis, existe uma estrutura de robô Wall-E (inspirado no filme "Wall-E"). Essa carcaça, impressa em 3D com base plástica, possui oito motores instalados e conta com um circuito de alimentação disponível (https://www.thingiverse.com/thing:3703555/files#google_vignette). O projeto está focado na movimentação desse robô, utilizando um ESP32 para controle via Wi-Fi.

 ![walle](https://github.com/user-attachments/assets/804b2c7f-31a3-4bba-8cde-305756952600)
 
 Fonte: (https://github.com/MatheusPinto/PI_IFSC_2023_02/tree/main/equipe_LuLu/conceive)

# Objetivo do Projeto
Desenvolver um sistema de movimentação para um robô Wall-E, visando a exploração de tecnologias IoT. O robô será controlado via Wi-Fi, utilizando o ESP32 como microcontrolador central, permitindo gerenciamento remoto.

# Componentes Principais
Estrutura do Robô Wall-E:
- Carcaça de plástico, impressa em 3D no LPAE do IFSC.
- 8 motores já instalados na estrutura.

Microcontrolador:
- ESP32: processador com conectividade Wi-Fi, permitindo comunicação web.

Circuito de Alimentação:
- Fonte de alimentação ja existente.

Interface Web:
- Desenvolvimento de uma interface simples e responsiva que permita o controle de direção e movimentação do robô remotamente.

# Funcionamento
Conectividade e Controle: 
O ESP32 será programado para se conectar à internet via Wi-Fi, estabelecendo uma rede local ou usando uma rede existente. Através da interface web, o usuário poderá controlar a movimentação do robô, ajustando comandos para os motores.

Interface Web:
A interface será projetada para enviar comandos ao ESP32, que controlará os motores do robô. Com uma interface gráfica intuitiva, o usuário poderá escolher direções (frente, ré, direita, esquerda) e ajustar a velocidade.


# Objetivo
A interface com o usuário que permita:
- Gerenciar o funcionamento dos motores.
- Operar o robô Wall-E remotamente via comunicação Wi-Fi.
- Controlar a direção e velocidade do robô.
- Ajustar a movimentação dos braços e da cabeça de Wall-E.

Ideias para Funcionalidades Extras, caso haja tempo adicional, considere implementar:
- Movimentos padronizados acionados com um único comando.
- Alto-falantes para simular sons e tornar o Wall-E mais interativo e expressivo.




