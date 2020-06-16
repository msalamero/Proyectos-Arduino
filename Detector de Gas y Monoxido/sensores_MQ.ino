#include <WiFi.h>
#include <PubSubClient.h>

//Variables de Sensores MQ
int VALOR_MQ5;
int VALOR_MQ7;
int BUZZER = 23;
char msg[25];

// Datos de Red WiFi y MQTTserver
const char* ssid = "xxx";
const char* password = "xxxx";
const char* mqtt_server = "xxxx.com.ar";
#define mqtt_port 1883
#define MQTT_USER "xxxxxxx"
#define MQTT_PASSWORD "xxxxx"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

//Funcion de conexion a WiFi
void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");

    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

//Función Reconect
void reconnect() {
   while (!client.connected()) {
     Serial.print("Attempting MQTT connection...");
     String clientId = "ESP32Client-";
     clientId += String(random(0xffff), HEX);
     if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
       Serial.println("connected");
       client.subscribe("gases");
     } else {
       Serial.print("failed, rc=");
       Serial.print(client.state());
       Serial.println(" try again in 5 seconds");
       delay(5000);
     }
  }
}

//Función Callback
void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------nuevo mensaje desde el broker -----");
    Serial.print("Topico:");
    Serial.println(topic);
    Serial.print("datos:");  
    Serial.write(payload, length);
    Serial.println();
}

void setup() {
  pinMode(BUZZER,OUTPUT); 
  //entradas analogicas, no requiere inicializacion
  Serial.begin(115200);
  Serial.setTimeout(500); 
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

//Funcion Loop (Principal)
void loop(){
client.loop();
//concentracion en sensor de CO (MQ7)
//INICIO -----------------------------------------------------------------------
float ppm_MQ7;
float sensor_volt_MQ7;
float RS_CO; 
float ratio_MQ7; 
int sensorValue_MQ7 = analogRead(39);

sensor_volt_MQ7=(float)(sensorValue_MQ7+1)/4095*5.0;
 
RS_CO = (5.0-sensor_volt_MQ7)/sensor_volt_MQ7;  // omitimos *RL
//-Reemplazamos "R0" con el nivel obtenido de los test -/
ratio_MQ7 = RS_CO/0.96; // ratio_MQ7 = RS/R0

ppm_MQ7 = (float)(97.651)*pow(ratio_MQ7,(-1.545));
if (ppm_MQ7<0)
ppm_MQ7=0;
if (ppm_MQ7>10000)
ppm_MQ7=10000;
//FINAL ---------------------------------------------------------------------------

 //concentracion en sensor de GAS (MQ5)
 //INICIO -----------------------------------------------------------------------
float ppm_MQ5;
float sensor_volt_MQ5;
float RS_gas; 
float ratio_MQ5; 
int sensorValue_MQ5 = analogRead(36);
 
sensor_volt_MQ5=(float)(sensorValue_MQ5+1)/4095*5.0;  

RS_gas = (5.0-sensor_volt_MQ5)/sensor_volt_MQ5; // omit *RL
//-Reemplazamos "R0" con el nivel obtenido de los test -/ 
ratio_MQ5 = RS_gas/630; // ratio_MQ5 = RS/R0

ppm_MQ5 = (float)77.829*pow(ratio_MQ5,(-2.522));
if (ppm_MQ5<0)
ppm_MQ5=0;
if (ppm_MQ5>10000)
ppm_MQ5=10000;
//FINAL ---------------------------------------------------------------------------
  
     //Programa de gases y buzzer
   VALOR_MQ5 = analogRead (36);
   VALOR_MQ7 = analogRead (39);
   Serial.print("ADC sensores:  "); //mostramos los valores del ADC diferentes a la concentración
   Serial.print(VALOR_MQ5);
   Serial.print(" , ");
   Serial.println(VALOR_MQ7);
   if(ppm_MQ5>1000){
   digitalWrite(BUZZER,HIGH);
   delay(500);
   digitalWrite(BUZZER,LOW);
   delay(500);  

   }
    if(ppm_MQ7>50){
   digitalWrite(BUZZER,HIGH);
   delay(200);
   digitalWrite(BUZZER,LOW);
   delay(100); 
   digitalWrite(BUZZER,HIGH);
   delay(200);
   digitalWrite(BUZZER,LOW);
   delay(500);
   }
    digitalWrite(BUZZER,LOW);

    //Datos a enviar aservidor
    String to_send = String(ppm_MQ5) + "," + String(ppm_MQ7) ;
    to_send.toCharArray(msg, 25);
    Serial.print("Publicamos mensaje -> ");
      Serial.println(msg);
     client.publish("gases", msg);
    delay(500);
 }
