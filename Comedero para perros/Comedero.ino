#include <Wire.h>
#include <NewPing.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include "HX711.h"
#include <Servo.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include <PubSubClient.h>
/*Declaración de variables para la balanza.*/
#define DOUT A1
Sensor de Peso.
#define CLK A0
HX711 balanza(DOUT, CLK);
float pesoActual=0;
bool movServ;
bool esHora;
//Asignamos al pin A1 como pin de Salida de Datos del
//Asignamos al pin A0 como pin de Reloj del Sensor de Peso.
//Definimos el Sensor de Peso.
//Arrancamos el peso del plato en 0.
//Corte de ciclo de servo
/*Declaración de variables para controlar el servo.*/
Servo servoMotor;
//Definimos el Servomotor.
/*Declaración de variables para el RTC.*/
//SDA=2.
//SCL=3.
tmElements_t tm;
//Definimos el RTC.
/*Aqui se configuran los pines donde debemos conectar el sensor*/
#define TRIGGER1_PIN 10
//Asignamos al pin 10 como pin de Disparo del Sensor
Ultrasónico 1.
#define ECHO1_PIN 11
//Asignamos al pin 11 como pin de Eco del Sensor
Ultrasónico 1.
#define TRIGGER2_PIN 5
//Asignamos al pin 5 como pin de Disparo del Sensor
Ultrasónico 1.
#define ECHO2_PIN 6
//Asignamos al pin 6 como pin de Eco del Sensor
Ultrasónico 1.
#define MAX_DISTANCE 200
//Máxima distancia que pueden medir los sensores.
NewPing sonar1(TRIGGER1_PIN, ECHO1_PIN, MAX_DISTANCE);
//Definimos el Sensor Ultrasónico 1.
NewPing sonar2(TRIGGER2_PIN, ECHO2_PIN, MAX_DISTANCE);
//Definimos el Sensor Ultrasónico 2.
int medicionComida=0;
//Arrancamos la medición de comida en 0.
int medicionAgua=0;
//Arrancamos la medición de agua en 0.
/*Definimos los horarios a los cuales el Pecopafe va a medir*/
int horas[5] = {7, 12, 22, 19, 20};
int minutos[5] = {5, 49, 40, 55, 13};
//Declaración de funciones.
float tomarPeso();
//Función para leer el peso del plato.
void leerHora();
//Función para llevar el conteo del tiempo.
void print2digits(int number);
//Función para imprimir por pantalla el tiempo actual.
void moverServo(float peso);
//Función para mover el servomotor según
especificaciones.
int depositoComida();
//Función para medir el depósito de comida.
int depositoAgua();
//Función para medir el depósito de agua.
void callback(char* topic, byte* payload, unsigned int length); //Función de captura de datos MQTT
void reconnect();
//Función de reconexión de MQTT
//Datos de conexión de WIFI
#define ssid
"Convivir"
#define pass
"7070707070"
//Datos de conexión de MQTT
#define clienteID
"01"
#define SERVER
"m15.cloudmqtt.com"
#define SERVERPORT
16539
#define USERNAME
"placa"
#define PASSWORD
"1234"
int status = WL_IDLE_STATUS; // the Wifi radio's status
const char* mensaje;
// Initialize the Ethernet client object
WiFiEspClient placa;
void callback(char* topic, byte* payload, unsigned int length);
void InitWiFi();
char Servir[] =
"Servir";
PubSubClient client(placa);
void setup()
{
Serial.begin(9600);
while (!Serial) ; // wait for serial
delay(200);
Serial1.begin(115200);
//Comprobar si el rtc funciona
leerHora();
//Sensor de peso y servo
Serial.println("---------------------------------------------------------------------------------------------------");
Serial.println("---------------------------------------------------------------------------------------------------");
Serial.print("Lectura del valor del ADC: ");
Serial.println("No ponga ningun objeto sobre la balanza");
Serial.println("Destarando...");
Serial.println("...");
balanza.set_scale(-424.61);
//Establecemos la escala definida por la
clase HX711.
balanza.tare(20);
movServ=false;
//WiFi
InitWiFi();
//connect to MQTT server
client.setServer(SERVER, SERVERPORT);
client.setCallback(callback);
}
void loop()
{
status = WiFi.status();
if ( status != WL_CONNECTED)
{
while ( status != WL_CONNECTED)
{
Serial.print("Intentando conectar a WPA SSID: ");
Serial.println(ssid);
// Connect to WPA/WPA2 network
status = WiFi.begin(ssid, pass);
delay(500);
}
Serial.println("Connectado al AP");
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);
}
if ( !client.connected() ) {
reconnect();
}
RTC.read(tm);
esHora=false;
for (int i=0;i<5;i++)
{
if (tm.Hour==horas[i] && tm.Minute==minutos[i])
{
esHora=true;
}
}
if (esHora && !movServ)
{
servoMotor.attach(9);
//Asignamos el Servomotor al pin 9.
pesoActual=tomarPeso();
moverServo(pesoActual);
client.publish("Plato","Se sirvio comida");
servoMotor.detach();
//Lo quitamos del pin 9.
pesoActual=tomarPeso();
client.publish("Plato", String(pesoActual).c_str());
medicionAgua=depositoAgua();
client.publish("Agua", String(medicionAgua).c_str());
delay(33);
//Tiempo prudente de espera entre una medición y otra de los sensores de distancia.
medicionComida=depositoComida();
client.publish("Comida", String(medicionComida).c_str());
}
else if (!esHora)
{
movServ=false;
}
client.loop();
}
int depositoComida()
{
int uS1 = sonar1.ping_median();
Serial.print("Cantidad de comida: ");
Serial.print(uS1 / US_ROUNDTRIP_CM);
Serial.println("cm");
uS1 = uS1 / US_ROUNDTRIP_CM;
return uS1;
} //Medición del sensor de distancia.
int depositoAgua()
{
int uS2 = sonar2.ping_median();
Serial.print("Cantidad de agua: ");
Serial.print(uS2 / US_ROUNDTRIP_CM);
Serial.println("cm");
uS2 = uS2 / US_ROUNDTRIP_CM;
return uS2;
} //Medición del sensor de distancia.
void moverServo(float peso)
{
if (peso>200)
{
movServ=true;
client.publish("Servir", "OFF"); //Como está lleno el plato, el servo no tira nada y le envía una señal de
apagado al switch de la app
}
else
{
Serial.print("Abrimos el servo");
while (!movServ)
{
servoMotor.write(120);
delay(300);
servoMotor.write(90);
peso=tomarPeso();
if (peso>200)
{
servoMotor.write(90);
movServ=true;
}
}
Serial.println("Se cerro el servo, Gramos: ");
Serial.println(peso);
}
}
float tomarPeso()
{
float p=balanza.get_units(5);
//El sensor de peso toma 20 mediciones del plato y calcula
un promedio, descontando el peso mismo del plato.
return p;
}
void leerHora()
{
if (RTC.read(tm))
{
}
else
{
if (RTC.chipPresent())
//Si el RTC se detiene, por el monitor serie se muestra el
mensaje de abajo. Hay que volver a setear el tiempo.
{
Serial.println("The DS1307 is stopped. Please run the SetTime");
Serial.println("example to initialize the time and begin running.");
Serial.println();
}
else
//Si se pierde la conexión con el RTC, por el monitor serie se
muestra el mensaje de abajo.
{
Serial.println("DS1307 read error! Please check the circuitry.");
Serial.println();
}
delay(9000);
}
delay(300);
}
void callback(char* topic, byte* payload, unsigned int length)
{
char PAYLOAD[5] = " ";
float peso=pesoActual;
Serial.print("Mensaje Recibido: [");
Serial.print(topic);
Serial.print("] ");
for (int i = 0; i < length; i++)
{
PAYLOAD[i] = (char)payload[i];
}
Serial.println(PAYLOAD);
if (String(topic) == String(Servir))
{
if (payload[1] == 'N')
{
servoMotor.attach(9);
pesoActual=tomarPeso();
moverServo(pesoActual);
servoMotor.detach();
client.publish("Servir", "OFF");
pesoActual=tomarPeso();
client.publish("Plato", String(pesoActual).c_str());
medicionAgua=depositoAgua();
client.publish("Agua", String(medicionAgua).c_str());
delay(33);
//Tiempo prudente de espera entre una medición y otra de los sensores de distancia.
medicionComida=depositoComida();
client.publish("Comida", String(medicionComida).c_str());
}
}
Serial.println();
}
void reconnect()
{
while (!client.connected())
{
Serial.print("Conectando al Broker ...");
// Loop hasta que se conecta
if ( client.connect(clienteID, USERNAME, PASSWORD) ) // connect (clientId, username, password)
{
Serial.println( "[OK]" );
client.subscribe("Plato");
client.subscribe("Servir");
client.subscribe("Comida");
client.subscribe("Agua");
}
else
{
Serial.print( "[FALLO] [ rc = " );
Serial.print( client.state() );
Serial.println( " : reintento en 5 segundos]" );
delay( 5000 );
}
}
}
void InitWiFi()
{
WiFi.init(&Serial1);
// inizializa el modulo ESP32
if (WiFi.status() == WL_NO_SHIELD)
// verifica que este presente
{
Serial.println("No se encuentra modulo WiFi ");
while (true);
//se detiene la ejecución
}
Serial.println("Conectando al Access Point ...");
while ( status != WL_CONNECTED) {
// intenta conectar a la red WiFi
Serial.print("Intentando conectar a la red SSID: ");
Serial.println(ssid);
status = WiFi.begin(ssid, pass);
delay(500);
}
Serial.println("Connectado al la red WiFi");
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);
}
