# Codigo de Arduino

```
#include <Keypad.h>   //incluye libreria para teclado matricial
#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>  // incluye libreria especifica para MFRC522
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <EEPROM.h>

#define RST_PIN 9  // constante para referenciar pin de reset
#define SS_PIN 10  // constante para referenciar pin de slave select

LiquidCrystal_I2C lcd(0x27, 20, 4);

MFRC522 lectorRF(SS_PIN, RST_PIN);  // crea objeto lectorRF enviando pines de slave select y reset

byte LecturaUID[4];                             // crea array para almacenar el UID leido
byte Usuario1[4] = { 0xC6, 0x77, 0xCC, 0x2B };  // UID de tarjeta leido en programa 1
//byte Usuario2[4]= {0x79, 0x0F, 0xEF, 0xC2} ;    // UID de llavero leido en programa 1

const byte ROWS = 4;  //cuatro columnas
const byte COLS = 4;  //tres columnas

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 7, 6, 5, 4 };      //conectar pins de fila
byte colPins[COLS] = { A0, A1, A3, A2 };  //conectar pins de columna

//constructor => 1)realiza un mapeo en(keys). 2 y 3) corresponde a los arrays donde colocamos los pines. 4 y 5) son las constantes. Son el num de filas y de columnas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
String entrada;
String newPass;
String modo = "inicio";
String pass = "191202";
bool accesoRF = false;
float sinVal;
int toneVal;
Servo servo;

void setup() {

  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  SPI.begin();              // inicializa bus SPI
  lectorRF.PCD_Init();      // inicializa modulo lector
  Serial.println("Listo");  // Muestra texto Listo
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Cerradura");
  lcd.setCursor(0, 1);
  lcd.print("Inteligente");
  servo.attach(8);
  servo.write(5);
  delay(2000);
  lcd.clear();
  Serial.begin(9600);  // inicializa comunicacion por monitor serie a 9600 bps
  bluetooth.begin(9600);
}



boolean comparaUID(byte lectura[], byte usuario[])  // funcion comparaUID
{
  for (byte i = 0; i < lectorRF.uid.size; i++) {  // bucle recorre de a un byte por vez el UID
    if (lectura[i] != usuario[i])                 // si byte de UID leido es distinto a usuario
      return (false);                             // retorna falso
  }
  return (true);  // si los 4 bytes coinciden retorna verdadero
}

void comprobarBluetooth() {
  if (bluetooth.available() > 0) {
    int res = bluetooth.read();
    Serial.println(res);
    if (res == 'a') {
      modo = "inicio";
    } else if (res == 'c') {
      modo = "activa";
    }
  }
}

//--------------------------

void loop() {

  char key = keypad.getKey();

  comprobarBluetooth();


  //armar alarma

  if (modo == "inicio") {

    lcd.setCursor(0, 0);
    lcd.print("Cerradura");
    lcd.setCursor(0, 1);
    lcd.print("Desarmada");
    modo = "desarmado";
  }


  //armar

  if (modo == "armar") {
    comprobarBluetooth();
    if (lectorRF.PICC_IsNewCardPresent()) {  // verificamos si se detecto nueva tarjeta
      if (lectorRF.PICC_ReadCardSerial()) {  // codigo de la tarjeta

        Serial.print("UID:");                           // muestra texto UID:
        for (byte i = 0; i < lectorRF.uid.size; i++) {  // bucle recorre de a un byte por vez el UID
          if (lectorRF.uid.uidByte[i] < 0x10) {         // si el byte leido es menor a 0x10
            Serial.print(" 0");                         // imprime espacio en blanco y numero cero
          } else {                                      // sino
            Serial.print(" ");                          // imprime un espacio en blanco
          }

          Serial.print(lectorRF.uid.uidByte[i], HEX);  // imprime el byte del UID leido en hexadecimal
          LecturaUID[i] = lectorRF.uid.uidByte[i];     // almacena en array el byte del UID leido
        }

        Serial.print("\t");  // imprime un espacio de tabulacion

        if (comparaUID(LecturaUID, Usuario1)) {  // llama a funcion comparaUID con Usuario1

          Serial.println("Bienvenido 1");  // si retorna verdadero muestra texto bienvenida
          modo = "activa";

        } else {
          lcd.clear();
          lcd.print("Tarjeta invalida");
          delay(1000);
          lcd.clear();
          lcd.print("Intente de nuevo");
        }


        lectorRF.PICC_HaltA();  // detiene comunicacion con tarjeta
      }
    }

    if (entrada.length() == 1) {
      lcd.clear();
      lcd.print("*");
    }

    if (key) {

      if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') {
        entrada += key;
        lcd.print("*");
      }

      if (key == 'B') {
        lcd.clear();
        entrada = "";
      }


      if (key == '#') {
        if (entrada == pass) {
          modo = "activa";
          entrada = "";
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Clave invalida");
          delay(1000);
          lcd.clear();
          lcd.print("Intente de nuevo");
          entrada = "";
        }
      }
    }
  }

  //activa

  if (modo == "activa") {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cerradura");
    lcd.setCursor(0, 1);
    lcd.print("Armada");
    servo.write(90);
    delay(2000);
    entrada = "";
    modo = "armado";
  }

  //armado


  if (modo == "armado") {
    comprobarBluetooth();
    if (key) {

      if (key == 'D') {
        modo = "desarmar";
        lcd.clear();
        lcd.print("Modo desarmar");
        delay(2000);
        lcd.clear();
        lcd.print("ingrese su clave");
        lcd.setCursor(0, 1);
        lcd.print("o tarjeta:");
      }
    }
  }

  //desarmar

  if (modo == "desarmar") {
    comprobarBluetooth();

    if (lectorRF.PICC_IsNewCardPresent()) {  // verificamos si se detecto nueva tarjeta
      if (lectorRF.PICC_ReadCardSerial()) {  // codigo de la tarjeta

        Serial.print("UID:");                           // muestra texto UID:
        for (byte i = 0; i < lectorRF.uid.size; i++) {  // bucle recorre de a un byte por vez el UID
          if (lectorRF.uid.uidByte[i] < 0x10) {         // si el byte leido es menor a 0x10
            Serial.print(" 0");                         // imprime espacio en blanco y numero cero
          } else {                                      // sino
            Serial.print(" ");                          // imprime un espacio en blanco
          }

          Serial.print(lectorRF.uid.uidByte[i], HEX);  // imprime el byte del UID leido en hexadecimal
          LecturaUID[i] = lectorRF.uid.uidByte[i];     // almacena en array el byte del UID leido
        }

        Serial.print("\t");  // imprime un espacio de tabulacion

        if (comparaUID(LecturaUID, Usuario1)) {  // llama a funcion comparaUID con Usuario1

          Serial.println("Bienvenido 1");  // si retorna verdadero muestra texto bienvenida
          lcd.clear();
          modo = "inicio";
        } else {
          lcd.clear();
          lcd.print("Tarjeta invalida");
          delay(1000);
          lcd.clear();
          lcd.print("Intente de nuevo");
          //tone(A1, toneVal);
        }


        lectorRF.PICC_HaltA();  // detiene comunicacion con tarjeta
      }
    }

    if (entrada.length() == 1) {
      lcd.clear();
      lcd.print("*");
    }

    if (key) {

      if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') {
        entrada += key;
        lcd.print("*");
      }

      if (key == 'B') {
        lcd.clear();
        entrada = "";
      }

      if (key == '#') {
        if (entrada == pass) {
          modo = "inicio";
          entrada = "";
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Clave invalida");
          delay(1000);
          lcd.clear();
          lcd.print("Intente de nuevo");
          entrada = "";
        }
      }
    }
  }

  //desarmado

  if (modo == "desarmado") {

    servo.write(5);
    comprobarBluetooth();

    if (key) {

      if (key == 'A') {
        modo = "armar";
        lcd.clear();
        lcd.print("Modo armar");
        delay(2000);
        lcd.clear();
        lcd.print("ingrese su clave");
        lcd.setCursor(0, 1);
        lcd.print("o tarjeta:");
      }

      if (key == 'C') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Cambiar clave");
        delay(1500);
        lcd.clear();
        lcd.print("clave actual:");
        modo = "cambiarPass";
      }
    }
  }

  //cambiar pass

  if (modo == "cambiarPass") {

    if (entrada.length() == 1) {
      lcd.clear();
      lcd.print("*");
    }

    if (key) {

      if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') {
        entrada += key;
        lcd.print("*");
      }

      if (key == 'B') {
        lcd.clear();
        entrada = "";
      }

      if (key == '#') {

        if (entrada == pass) {
          lcd.clear();
          entrada = "";
          modo = "repetirPass";
          delay(500);
          lcd.print("Su nueva clave:");
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Clave invalida");
          delay(1000);
          lcd.clear();
          lcd.print("Intente de nuevo");
          entrada = "";
        }
      }
    }
  }


  //repetir pass

  if (modo == "repetirPass") {

    if (entrada.length() == 1) {
      lcd.clear();
      lcd.print("*");
    }

    if (key) {

      if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') {
        entrada += key;
        lcd.print("*");
      }

      if (key == 'B') {
        lcd.clear();
        entrada = "";
      }

      if (key == 'C') {
        pass = entrada;
        lcd.clear();
        lcd.print("contra cambiada!");
        delay(2000);
        lcd.clear();
        entrada = "";
        modo = "inicio";
      }
    }
  }
}
```
