# On-Air-Manager

## A iniciativa

A bandAlegre é uma banda cristã, jovem e marista que tem vindo crescendo aos poucos quer em qualidade como em seguidores. 

Devido ao Covid-19, a bandAlegre necessitou de arranjar uma maneira de continuar a fazer os seus concertos mesmo sem a possibilidade de ajuntamentos. A solução foi começar a transmitir os mesmo.
Para isso, eu e uma equipa fomos chamados e responsabilizados por vários aspetos da gravação, transmissão e comunicação com o público.
Um dos fatores que mais dificultou este processo de transmissão foi a comunicação entre o editor de vídeo em tempo real e os *Câmeras*.
Por esse motivo, decidi criar este sistema para tentar resolver esse problema.

## A solução

Esta solução recorre à placa **NodeMCU** tanto para o servidor como para os diferentes clientes.
O servidor tem a si ligada quatro interruptores de duas posições e quatro LED's, pois corresponde ao número de câmaras máximo usualmente usadas, mas isto é expansível dependendo das capacidades da versão da placa usada.
A comunicação entre placas é feita através do protocolo de transferência de pacotes UDP, sendo cada pacote direcionado diretamente para a placa escolhida aquando da mudança de estado do interruptor. Tem o seguinte funcionamento:

                                    Mudança no Interruptor

                                            +
                                            |
                                            |
                     Mudança de Estado  <---+
                   Do LED Correspondente    |
                                            |
                                            v

                        Atualização do Estado Assinalado No Servidor

                                            +
                                            |
                                            |
                                            |
                                            |
                                            v
                                                                                
                              Servidor Manda um pacote com a
                                Informação para o Cliente
                                     Correspondente

                                            +
                                            |
                                            |
                                            |
                                            |
                                            v

                            Cliente recebe o pacote e processa,ligando
                              a Luz que Confirma que a Câmara
                                a que está associado está
                                        "No Ar"

###   O circuito
  **Servidor**

   O circuito do Servidor é muito simples e consiste num NodeMCU ao qual se encontram 4 alavancas de duas posições em que se indicam quais as câmaras que estão a transmitir. A cada switch corresponde um LED para garantir que a placa detetou as mudanças de sinal dos botões. Para a ligação das alavancar recorreu-se ao tradicional circuito com uma resistência *pull-down*, esta resistência com valor de cerca de 100 ohms, tem como objetivo evitar oscilações aleatórias do valor de leitura do pin correspondente, obrigando a que quando a alavanca se encontra desligada (para baixo), o valor é efetivamente *LOW*. Dada a placa usada fornecer cerca 3.3V, os LED's usados encontram-se ligados diretamente à placa, mas caso a placa forneça 5V, é aconselhado ligar uma resitência em série para evitar que o LED queime.

   ![Imagem do Circuito do Servidor](https://github.com/ManuelFSousa/On-Air-Cameras-Manager/blob/main/Diagramas/Circuito_Servidor.png)

   **Cliente**
   
   *Em Desenvolvimento*

### Como Usar?
   Para usar este código, recorre-se à ARDUINO IDE. Após a instalação da placa, é importante editar previamente o ficheiro "WiFi-Config-ex.hpp" previamente, da forma indicada no mesmo, e renomeando-o posteriormente para "WiFi-Config.hpp". Após esse passo é só escolher a respetiva placa, qual a porta COM a que se encontra ligada e dar upload do ficheiro como normalmente é feito num arduino.

## Em desenvolvimento

Os códigos tanto do servidor como do cliente já foram testados com uma placa real e recorrendo a um programa de receção e envio de pacotes UDP. Falta testar no entanto num ambiente completamente real, apenas com placas e um ponto de acesso.

## Objetivos Futuros

Se possível desenhar uma caixa impressa em 3D e que tenha encaixa para a sapata do flash das câmaras.
Criar uma ligação com a mesa de mistura de vídeo para a transição dos sinais no servidor ser automática.