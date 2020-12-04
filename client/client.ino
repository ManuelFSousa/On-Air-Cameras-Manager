/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                         Codigo desenvolvido por: Manuel Sousa                                       //
//                                        bandAlegre                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>

const char* ssid = "definir";
const char* password = "definir";

IPAddress(192, 168, 13, 80)
WiFiClient client;

void setup(){
    Serial.begin(115200); 

    //-----------------------------------Ligação ao WIFI-----------------------------------
    WiFi.begin(ssid, password); 
    Serial.println("**************Servidor de câmaras no ar da bandAlegre**************");
    Serial.println("\nA conectar ao WIFI "); Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConexão bem sucedida!");
    Serial.println("O IP do servidor é: "); Serial.print(WiFi.localIP());
    //---------------------------------------------------------------------------------------~

    //--------------------------------Setup dos Pinos a usar---------------------------------
    pinMode(D5, OUTPUT); //Pin do LED
    //---------------------------------------------------------------------------------------
}

void loop(){
    int statusAtual;

    client.connect(server,80);
    String status = client.readStringUntil('\r');
    Serial.println("Server Status: " + answer);

    if(answer[3] == '1'){                           //Trocar o valor de 1 para o número da câmara corresponde ao dispositivo para qual este código vai ser carregado
        digitalWrite(D5, atoi(answer[7]));
        statusAtual = atoi(answer[7]);
    }
    Serial.println("Status Atual: " + statusAtual);
    client.println("Status Camâra 1: " + statusAtual); //Trocar o valor de 1 para o número da câmara corresponde ao dispositivo para qual este código vai ser carregado
    delay(1500);
    client.flush();
}
//LedX = 1/0