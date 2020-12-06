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
A comunicação entre placas é feita através de *HTTP* (Não confirmado) e tem o seguinte funcionamento:

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
                                                                                
                              Cliente Correspondente Deteta
                            a Mudança através do Método Get

                                            +
                                            |
                                            |
                                            |
                                            |
                                            v

                              Cliente a Luz que Confirma que
                            a Câmara a que está associado está
                                          "On air"

###   O circuito
  **Servidor**
   O circuito do Servidor é muito simples e consiste num NodeMCU ao qual se encontram 4 alavancas de duas posições em que se indicam quais as câmaras que estão a transmitir. A cada switch corresponde um LED para garantir que a placa detetou as mudanças de sinal dos botões.

   ![Imagem do Circuito do Servidor](https://github.com/ManuelFSousa/On-Air-Cameras-Manager/blob/main/Diagramas/Circuito_Servidor.png)

   **Cliente**
   *Em Desenvolvimento*

## Em desenvolvimento

De momento encontra-se tudo ainda em prototipagem e este código não foi testado devido à falta de todo o material necessário.

## Objetivos Futuros

Se possível desenhar uma caixa impressa em 3D e que tenha encaixa para a sapata do flash das câmaras.
Criar uma ligação com a mesa de mistura de vídeo para a transição dos sinais no servidor ser automática.