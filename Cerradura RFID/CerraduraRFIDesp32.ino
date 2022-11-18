// proyecto esp32 4/11/22


#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Ubidots.h"

#define SS_PIN  5  //D4
#define RST_PIN  27 //D3
#define lock 1 //tx
#define G 5 //D1
#define R 16 //D0
#define bl 15 //D8

const char* UBIDOTS_TOKEN = "BBFF-iIcrhEkjVy5105EolLRS6gkKxCD8J1";  
const char* WIFI_SSID = "UBP";     
const char* WIFI_PASS = "pascal25";     
const char* DEVICE_LABEL = "rfid";    

Ubidots ubidots(UBIDOTS_TOKEN, UBI_UDP);


LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 mfrc522(SS_PIN, RST_PIN);   

const int cantidad = 8;
int cantidadActual = 1;

//Tarjetas con Acceso

String paseMaster = "89 B1 00 8E";
String pases[cantidad] = {"B9 B4 6A 8E","89 5F 07 B4"};
String nombres[cantidad] = {"Tarjeta 1","Tarjeta 2" }; 

/////////////////////////////////////////

int acceso = 0;
int out = 0;
String llave;
int x= -1 ;



void setup()
{
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  Wire.begin(21, 22); // Iniciar I2C
  SPI.begin();      // Iniciar SPI
  mfrc522.PCD_Init();   // Iniciar MFRC522
  pinMode(R, OUTPUT);
  digitalWrite(R, HIGH);
  pinMode(G, OUTPUT);
  digitalWrite(G, HIGH);
  pinMode(lock, OUTPUT);
  digitalWrite(lock, HIGH);
  pinMode(bl, OUTPUT);
  lcd.begin();  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Laboratorio");
  Serial.begin(9600);
}
void loop()
{ 
  lcd.setCursor(0, 0);
  lcd.print(" Laboratorio:");
  lcd.setCursor(0, 1);
  lcd.print(" MUESTRE LLAVE");
  
  if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
    return;
  }
  
  Serial.println();
  
  llave = leerLlave();
  
  Serial.println("Lei la llave:" + llave);

  if ( llave == paseMaster){
      agendarTarjeta();
      return;
  }
  
  acceso = verificarTarjeta(acceso);
  Serial.println("VAR acceso: " + String(acceso));
  if ( acceso == 1 ){
    ingresaTarjeta();
    registrarUbidots();
  }else{
    noIngresaTarjeta();
  }
  acceso = 0;
}

void ingresaTarjeta(){
  Serial.println("Ingresa funcion ingresaTarjeta");

  // Escribo en LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BIENVENIDO:");
  lcd.setCursor(0, 1);
  lcd.print(nombres[x]);

  // Abro y cierro relay
  digitalWrite(G, LOW);
  digitalWrite(lock, LOW);
  digitalWrite(bl, HIGH);
  delay(4000); 
  digitalWrite(G, HIGH);
  digitalWrite(lock, HIGH);
  digitalWrite(bl, LOW);
  
  lcd.clear();
}

void noIngresaTarjeta() {
  Serial.println("Ingresa funcion noIngresaTarjeta");
  
  // Escribo en LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Laboratorio:");
  lcd.setCursor(2, 1);
  lcd.print("DESCONOCIDO");

  delay(2000);
  
  lcd.clear();
}

int verificarTarjeta(int acceso) {
  Serial.println("Ingresa funcion verificarTarjeta");
  for (int y = 0; y < cantidad; y++) {
    if (llave == pases[y]) {
      acceso = 1;
      x = y;
    }
  }
  return acceso; 
}

void registrarUbidots() {
  Serial.println("Registrando");
  char str[11];
  nombres[x].toCharArray(str, sizeof(nombres[x]));
  ubidots.addContext("Entró", str);
  char* context = (char*)malloc(sizeof(char) * 60);
  ubidots.getContext(context);
  ubidots.add("asistencia", 1, context);  // Cambiar con el nombre de tu variable
  bool bufferSent = false;
  bufferSent = ubidots.send(DEVICE_LABEL);  
  free(context);
  Serial.println("Registre");
}

void agendarTarjeta(){
  boolean hecho = false;
  boolean duplicada = false;
  String newLlave = "";
  lcd.clear();
  while (!hecho){
    
    lcd.setCursor(2, 0);
    lcd.print("Leyendo:");
    lcd.setCursor(2, 1);
    lcd.print("Tarjeta");
    if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
      continue;
    }
    
    if(cantidadActual >= cantidad){
      Serial.println("Cantidad de llaves max " + String(cantidad));
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Cantidad");
      lcd.setCursor(2, 1);
      lcd.print("Maxima");
      delay(2000);
      lcd.clear();
      return;
    }
    newLlave = leerLlave();
    if (newLlave == paseMaster){
      continue;  
    }
    for (int y = 0; y < cantidad; y++) {
      if (newLlave == pases[y]) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Tarjeta");
        lcd.setCursor(2, 1);
        lcd.print("Duplicada");
        delay(2000);
        lcd.clear();
        duplicada = true;
        break;
      }
    }
    if ( duplicada ){
      duplicada = false;
      continue;  
    }
    pases[cantidadActual] = newLlave;
    nombres[cantidadActual] = "Tarjeta " + String(cantidadActual + 1);
    cantidadActual++;
    
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Tarjeta");
    lcd.setCursor(2, 1);
    lcd.print("Registrada");
    delay(2000);
    lcd.clear();
    
    hecho = true; 
  } 
  Serial.println("Agende la nueva llave: " + llave);
}

String leerLlave(){
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  llave = content.substring(1);
  return llave; 
}
