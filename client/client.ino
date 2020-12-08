/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                         Codigo desenvolvido por: Manuel Sousa                                       //
//                                        bandAlegre                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <WiFiUdp.h>
#include <strings.h>
#include "WiFi_Config.hpp"

const char* ssid = ssidConfig;
const char* password = passConfig;

IPAddress ip(192, 168, 1, 14); //Trocar o 14, para 15, 16 e 17, entre placas diferentes
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

unsigned int localUdpPort = 2461; //Trocar o 2461, para 2462, 2463 e 2464, entre placas diferentes
char pacote_recebido[10];
WiFiUDP Udp;

void setup(){
    Serial.begin(115200); 

    //-----------------------------------Ligação ao WIFI-----------------------------------
    WiFi.begin(ssid, password); 
    Serial.println("**************Cliente de câmaras no ar da bandAlegre**************");
    Serial.println("\nA conectar ao WIFI "); Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConexão bem sucedida!");
    Serial.println("O IP do Cliente é: "); Serial.print(WiFi.localIP()); Serial.print(":2461");
    //---------------------------------------------------------------------------------------~
    Udp.begin(localUdpPort);
    //--------------------------------Setup dos Pinos a usar---------------------------------
    pinMode(D5, OUTPUT); //Pin do LED
    //---------------------------------------------------------------------------------------
}

void loop(){
    int statusAtual;
    pacote_recebido[3] = '\0';      //Para evitar entrar sempre no segundo if

    int tamanhoPacote = Udp.parsePacket();
    if(tamanhoPacote){
        Serial.printf("\n\nRecebido %d bytes do IP %s, através da porta %d", tamanhoPacote, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        Udp.read(pacote_recebido, 10);
        Serial.printf("\nConteúdo do Pacote: %s", pacote_recebido);
    }

    if(pacote_recebido[3] == '1'){                                   //Trocar o valor de 1 para o número da câmara corresponde ao dispositivo para qual este código vai ser carregado
        digitalWrite(D5, pacote_recebido[7] - '0');                 //Subtrai-se o valor char de 0 de modo a obter o valor inteiro de pacote_recebido[7]
        statusAtual = (pacote_recebido[7] - '0');
        Serial.print("\nStatus Atual: "); Serial.print(statusAtual);
    }
    delay(1000);
}