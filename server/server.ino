/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                         Codigo desenvolvido por: Manuel Sousa                                       //
//                                        bandAlegre                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <strings.h>
#include "WiFi_Config.hpp"

#define B1 D0
#define B2 D1
#define B3 D2
#define B4 D4               //Evitar usar o pin D3, pois se puxado a LOW, o NodeMCU não vai conseguir inicializar. (Como alternativa, pode ser usado para o botão, estando este premido)
#define L1 D5
#define L2 D6
#define L3 D7
#define L4 D8

const char* ssid = ssidConfig;
const char* password = passConfig;

IPAddress ip(192, 168, 1, 13);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

IPAddress ipCamera1(192,168,1,14);
IPAddress ipCamera2(192,168,1,15);
IPAddress ipCamera3(192,168,1,16);
IPAddress ipCamera4(192,168,1,17);
int portaCamera1 = 2461;
int portaCamera2 = 2462;
int portaCamera3 = 2463;
int portaCamera4 = 2464;

unsigned int localUdpPort = 2460;
WiFiUDP Udp;

int envia_pacote(char* mensagem, IPAddress ipCamera, int portaCamera);

void setup(){
    Serial.begin(115200); 
    
    //-----------------------------------Ligação ao WIFI-----------------------------------
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password); 
    Serial.flush();
    Serial.print("\n\n**************Servidor de câmaras no ar da bandAlegre**************");
    Serial.println("\nA conectar ao WIFI "); Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nConexão bem sucedida!");
    Serial.print("\nO IP do servidor é: "); Serial.print(WiFi.localIP()); Serial.print(":2460");
    //---------------------------------------------------------------------------------------
    Udp.begin(localUdpPort);
    //--------------------------------Setup dos Pinos a usar---------------------------------
    pinMode(B1, INPUT); //Pin Botão 1
    pinMode(B2, INPUT); //Pin Botão 2
    pinMode(B3, INPUT); //Pin Botão 3
    pinMode(B4, INPUT); //Pin Botão 4
    pinMode(L1, OUTPUT); //Pin do LED 1
    pinMode(L2, OUTPUT); //Pin do LED 2
    pinMode(L3, OUTPUT); //Pin do LED 3
    pinMode(L4, OUTPUT); //Pin do LED 4
    //---------------------------------------------------------------------------------------
}

void loop(){
    int estado1 = digitalRead(B1), estado2 = digitalRead(B2), estado3 = digitalRead(B3), estado4 = digitalRead(B4);
    char mensagem[9];
    
    while(1){
        strcpy(mensagem, "Led2 = c");

        if(digitalRead(B1) != estado1){
            estado1 = digitalRead(B1);
            Serial.print("\nPino1: "); Serial.print(digitalRead(B1));
            digitalWrite(L1, digitalRead(B1));
            mensagem[3] = '1';
            mensagem[7] = 48 + digitalRead(B1); //Adiciona-se 48 porque é o número correspondente a 0 na tabela ascii. Caso o input esteja a 0, o char fica a 0, se estiver a 1, o char fica a 1
            envia_pacote(mensagem, ipCamera1, portaCamera1);
        }
        
        if(digitalRead(B2) != estado2){
            estado2 = digitalRead(B2);
            Serial.print("\nPino2: "); Serial.print(digitalRead(B2));
            digitalWrite(L2, digitalRead(B2));
            mensagem[3] = '2';
            mensagem[7] = 48 + digitalRead(B1); //Adiciona-se 48 porque é o número correspondente a 0 na tabela ascii. Caso o input esteja a 0, o char fica a 0, se estiver a 1, o char fica a 1
            envia_pacote(mensagem, ipCamera2, portaCamera2);
        }
        
        if(digitalRead(B3) != estado3){
            estado3 = digitalRead(B3);
            Serial.print("\nPino3: "); Serial.print(digitalRead(B3));
            mensagem[3] = '3';
            mensagem[7] = 48 + digitalRead(B1); //Adiciona-se 48 porque é o número correspondente a 0 na tabela ascii. Caso o input esteja a 0, o char fica a 0, se estiver a 1, o char fica a 1
            envia_pacote(mensagem, ipCamera3, portaCamera3);
        }
        
        if(digitalRead(B4) != estado4){
            estado4 = digitalRead(B4);
            Serial.print("\nPino4: "); Serial.print(digitalRead(B4));
            mensagem[3] = '4';
            mensagem[7] = 48 + digitalRead(B1); //Adiciona-se 48 porque é o número correspondente a 0 na tabela ascii. Caso o input esteja a 0, o char fica a 0, se estiver a 1, o char fica a 1
            envia_pacote(mensagem, ipCamera4, portaCamera4);
        }
        delay(500);
    }    
}

int envia_pacote(char* mensagem, IPAddress ipCamera, int portaCamera){
    if(Udp.beginPacket(ipCamera, portaCamera) == 0)
        return 0;

    Udp.write(mensagem);
    
    Udp.endPacket();
    if(Serial.print("\nPackage sent") == 0)
        return 0;

    return 1;
}