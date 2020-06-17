#include "EspMQTTClient.h"
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <DHT11.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3               
OneWire oneWire(ONE_WIRE_BUS);                                     
DallasTemperature sensors(&oneWire); 




const int DS_PIN = 3;
const int PinTrig = 4;                     // Pines del sensor Trigger y Echo
const int PinEcho = 5;
const float VelSon = 34000.0;              // Constante velocidad sonido en cm/s
const int numLecturas = 5;                 // Número de muestras
float lecturas[numLecturas];               // Array para almacenar lecturas
int lecturaActual = 0;                     // Lectura por la que vamos
float total = 0;                           // Total de las que llevamos
float media = 0;                           // Media de las medidas
bool primeraMedia = false;                 // Para saber que ya hemos calculado por lo menos una media
float tanque_nivel = 0;
int tanque_ingreso = 18;                   // Pin de presión de agua
char* a;
int ingreso;
char msg[25];
long lastMsg = 0;
int tanque_text = 23;                       // Pin temperatura interior
int err_ext;
float temp_int;
float temp_ext, hum_ext;
DHT11 dht11_ext(tanque_text);




EspMQTTClient client(
  "UBP",                     // Red WiFi
  "pascal25",         
  "iot.edurobots.com.ar",    // IP del broker MQTT
  "web_client",              
  "1234",                    // Contraseña
  "tanque",                  // Nombre del cliente
  1883                       // Puerto MQTT
);


void setup() {
  Serial.begin(115200);
  sensors.begin();
  client.enableDebuggingMessages();        // Habilita los mensajes por el puerto serie
  pinMode(PinTrig, OUTPUT);               
  pinMode(PinEcho, INPUT);
  pinMode(tanque_text, INPUT);
  pinMode(tanque_ingreso, INPUT);
  for (int i = 0; i < numLecturas; i++) {  
    lecturas[i] = 0;
  }
}


void onConnectionEstablished() {
  client.subscribe("tanque", [] (const String & payload)  {
    Serial.println(payload);
  });
}



void loop() {
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    total = total - lecturas[lecturaActual];            // Se elimina la última medida
    iniciarTrigger();
    unsigned long tiempo = pulseIn(PinEcho, HIGH);      // La función pulseIn obtiene el tiempo...
                                                        // ...que tarda en cambiar entre estados,...
                                                        // en este caso a HIGH
    float distancia = tiempo * 0.000001 * VelSon / 2.0; // Se obtiene la distancia en cm, hay que...
                                                        // ...convertir el tiempo en segudos ya que... 
                                                        // ...está en microsegundos,...
                                                        // ...por eso se multiplica por 0.000001    
    lecturas[lecturaActual] = distancia;                // Se almacena la distancia en el array
    total = total + lecturas[lecturaActual];            // Se añade la lectura al total
    lecturaActual = lecturaActual + 1;                  // Se avanza a la siguiente posición del array
    if (lecturaActual >= numLecturas) {                 // Se comprueba si se ha llegado al final del array
      primeraMedia = true;
      lecturaActual = 0;
    }
    media = total / numLecturas;                        // Se calcula la media
    tanque_nivel = media;
    if ((err_ext = dht11_ext.read(hum_ext, temp_ext)) == 0) {  // Si devuelve 0 es que ha leido bien
      Serial.print("Temperatura: ");
      Serial.print(temp_ext);
      Serial.print(" Humedad: ");
      Serial.print(hum_ext);
      Serial.println();
    } else {
      Serial.println();
      Serial.print("Error Num :");
      Serial.print(err_ext);
      Serial.println();
    }
    sensors.requestTemperatures();             // Se recibe la lectura del sensor sumergible
    temp_int = sensors.getTempCByIndex(0);
    ingreso = digitalRead(tanque_ingreso);
    if (ingreso == 0) {
      a = "No hay presión de agua";
    } else {
      a = "Hay presión de agua";
    }
    tanque_nivel = tanque_nivel/100;
    tanque_nivel = 3.1415*(0.25)*tanque_nivel;
    tanque_nivel = tanque_nivel*1000;
    tanque_nivel = 1000-tanque_nivel;
    String to_send2 = String(temp_int) + "," + String(temp_ext)  + "," + String(tanque_nivel)+ "," + String(a);
    to_send2.toCharArray(msg, 50);
    Serial.print("Publicamos info tanque -> ");
    Serial.println(msg);
    client.publish("tanque", msg);
  }
}



void iniciarTrigger() {            // Función que inicia la secuencia del Trigger para comenzar a medir
  digitalWrite(PinTrig, LOW);      // Se pone el Trigger en estado bajo y se espera 2 us
  delayMicroseconds(2);
  digitalWrite(PinTrig, HIGH);     // Se pone el pin Trigger a estado alto y se espera 10 us
  delayMicroseconds(10);
  digitalWrite(PinTrig, LOW);      // Se comienza poniendo el pin Trigger en estado bajo
}



void callback(char* topic, byte* payload, unsigned int length) {
  char PAYLOAD[5] = "    ";
  char tanque[] = "tanque";
  Serial.print("Mensaje Recibido: [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    PAYLOAD[i] = (char)payload[i];
  }
  Serial.println(PAYLOAD);
}
