/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                         Codigo desenvolvido por: Manuel Sousa                                       //
//                                        bandAlegre                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>

const char* ssid = "definir";
const char* password = "definir";

IPAddress ip(192, 168, 13, 80);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
WiFiServer server(80);

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
    Serial.println("\nConexão bem sucedida!");
    Serial.println("O IP do servidor é: "); Serial.print(WiFi.localIP());
    //---------------------------------------------------------------------------------------
    server.begin();
    //--------------------------------Setup dos Pinos a usar---------------------------------
    pinMode(D1, INPUT); //Pin Botão 1
    pinMode(D2, INPUT); //Pin Botão 2
    pinMode(D3, INPUT); //Pin Botão 3
    pinMode(D4, INPUT); //Pin Botão 4
    pinMode(D5, OUTPUT); //Pin do LED 1
    pinMode(D6, OUTPUT); //Pin do LED 2
    pinMode(D7, OUTPUT); //Pin do LED 3
    pinMode(D8, OUTPUT); //Pin do LED 4
    //---------------------------------------------------------------------------------------
}

void loop(){
    int estado1 = digitalRead(D1), estado2 = digitalRead(D2), estado3 = digitalRead(D3), estado4 = digitalRead(D4);
    WiFiClient client = server.available();
    
    while(1){
        if(digitalRead(D1) != estado1){
            estado1 = digitalRead(D1);
            Serial.print("\nPino1: "); Serial.print(digitalRead(D1));
            digitalWrite(D5, digitalRead(D1));
            client.printf("Led1 = %d", digitalRead(D1));
        }
        else if(digitalRead(D2) != estado2){
            estado2 = digitalRead(D2);
            Serial.print("\nPino2: "); Serial.print(digitalRead(D2));
            digitalWrite(D6, digitalRead(D2));
            client.printf("Led2 = %d", digitalRead(D2));
        }
        else if(digitalRead(D3) != estado3){
            estado3 = digitalRead(D3);
            Serial.print("\nPino3: "); Serial.print(digitalRead(D3));
            digitalWrite(D7, digitalRead(D3));
            client.printf("Led3 = %d", digitalRead(D3));
        }
        else if(digitalRead(D4) != estado4){
            estado4 = digitalRead(D4);
            Serial.print("\nPino4: "); Serial.print(digitalRead(D4));
            digitalWrite(D8, digitalRead(D4));
            client.printf("Led4 = %d", digitalRead(D4));
        }
        client.flush();
        delay(500);
    }    
}
//LedX = 1/0
