//NOMBRE: MODULOX
//AUTOR1: Mercado Agustin
//AUTOR2: Delgado Facundo
//MATERIA: Tecnicas Digitales 2
//INSTITUCION: Universidad Blas Pascal
//FECHA ULTIMA ACTUALIZACION: 19/11/2019


#include "EspMQTTClient.h"
#include <DHT.h> 
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Variables globales
int temp1 = 0;
int temp2 = 1;
long lastMsg = 0;
char msg[25];

//topicos
// temperatura - "room/temp" 
// luz - "room/ligth" - on/off
// toma - "room/swich" on/off
//mensaje de estado - "data/state"
EspMQTTClient client(
//"Depto-Mercado-2.4G",
//"P1111111P",
  //"Mercado Ale-2.4G",
  //"154305177",
  "UBP",
  "pascal25",
  //"soldier.cloudmqtt.com",  // MQTT Broker server ip
  "xxxxxxxx",  // MQTT Broker server ip
  //"MODULOX",   // Can be omitted if not needed
  "web_client",   // Can be omitted if not needed
  //"admin",   // Can be omitted if not needed
  "xxxxxx",   // Can be omitted if not needed
  "MODULOX",      // Client name that uniquely identify your device
  //18629              // The MQTT port, default to 1883. this line can be omitted
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup() {
 dht.begin();
  pinMode(2,OUTPUT);
   pinMode(0,OUTPUT);
  // digitalWrite(0,LOW);
  Serial.begin(115200);
  
  client.enableDebuggingMessages(); // habilita los mensajes por el puerto serie
}

void onConnectionEstablished() {
  digitalWrite(0,HIGH);
  

  client.subscribe("room/light", [] (const String &payload)  {
    Serial.println(payload);
    
    
    if(payload[1]== 'f')////////condicion que enciende la luz
    {
      Serial.println("Luz encendida");
      digitalWrite(2,LOW);
    }
    
    
    if(payload[1] == 'n')//////////condicion que apaga la luz
    {
     Serial.println("Luz apagada");
     digitalWrite(2,HIGH);
     }
  });

  client.subscribe("room/switch", [] (const String &payload)  {
    Serial.println(payload);
    
    
    if(payload[1]== 'n')////////condicion que enciende la luz
    {
      Serial.println("Toma encendida");
      digitalWrite(0,LOW);
    }
    
    
    if(payload[1] == 'f')//////////condicion que apaga la luz
    {
     Serial.println("Toma apagado");
     digitalWrite(0,HIGH);
     }    
  });

  client.publish("data/state", "Conexion establecida\nEnviando y recibiendo datos...");
  client.publish("temp", msg);////ENVIO DE DATOS DE TEMPERATURA
}

void loop() {
  //digitalWrite(0,LOW);
  //float t;
  

  client.loop();

long now = millis();

if (now - lastMsg > 5000)
{

lastMsg = now;

temp1++;

temp2++;
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Check if any reads failed and exit early (to try again).

if (isnan(t)) {

Serial.println(F("Error al leer sensor DHT!"));

return;

}
String to_send = String(t,1);

to_send.toCharArray(msg, 25);
Serial.print("La temperatura actual es: ");

Serial.println(msg);

client.publish("room/temp", msg);////ENVIO DE DATOS DE TEMPERATURA
client.publish("data/state", "Conexion establecida\nEnviando y recibiendo datos...");
}
}
