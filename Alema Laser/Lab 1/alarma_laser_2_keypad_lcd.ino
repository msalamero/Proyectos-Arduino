#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String entrada;
String modo = "inicio";
String pass = "1234";
bool detectado = false;

void setup()
{

  pinMode(A1, INPUT); // Pin fotoresistencia
  pinMode(5, OUTPUT); // Pin buzzer
  pinMode(4, OUTPUT); // Pin laser
  lcd.begin();
  lcd.backlight();
  lcd.print("LBDL Alarma 1.0");
  delay(2000);
  lcd.clear();
  lcd.print("DESACTIVADO");
  Serial.begin(9600);
}



void loop()
{
  char key = keypad.getKey();

  //:::::::::::::::ARMAR ALARMA::::::::::::::::::::
  if (modo == "armar") {
    if (key) {
      entrada += key;

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        lcd.print('*');
      }

      if (key == 'B') {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }

      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        if (entrada == pass) {
          activacion();
          digitalWrite(4, HIGH);
          escribir("ACTIVADO", 0, 0);
          modo = "activa";
          key = '\0';
          entrada = "";
        } else {
          escribir("Error!", 5, 0);
          entrada = "";
          tone(5, 100, 1000);
          delay(1000);
          armar();
        }
      }

      if (key == 'D') {
        modo = "inicio";
        escribir("DESACTIVADO", 0, 0);
      }
    }
  }



  //::::::::::::::::INICIO::::::::::::::::::::
  if (modo == "inicio") {
    if (key) {

      if (key == 'A') {
        modo = "armar";
        armar();
      }

      if (key == 'C') {
        modo = "cambiarpass";
        key = '\0';
        cambiarPass();
      }
    }
  }


  //::::::::::::::::ACTIVA::::::::::::::::::::
  if (modo == "activa") {
    if (key) {

      if (key == 'A') {
        modo = "desarmar";
        key = '\0';
        desarmar();
      }
    }

    int ldr = analogRead(A1);

    if (ldr > 500) {
      detectado = true;
    }

  }


  if (detectado) {
    tone(5, 500, 1000);
    Serial.println("detectado!");
  }




  //::::::::::::::::DESARMAR::::::::::::::::::::
  if (modo == "desarmar") {
    if (key) {
      entrada += key;
      Serial.println(entrada);

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        //lcd.print(key);
        lcd.print('*');
      }

      if (key == 'B') {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }

      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        if (entrada == pass) {
          detectado = false;
          escribir("DESACTIVADO", 0, 0);
          digitalWrite(4, LOW);
          modo = "inicio";
          key = '\0';
          entrada = "";
          tone(5, 300, 500);
          delay(100);
          tone(5, 500, 500);

        } else {
          escribir("Error!", 5, 0);
          entrada = "";
          tone(5, 100, 1000);
          delay(1000);
          desarmar();
        }
      }

    }
  }


  //::::::::::::::::CAMBIAR PASSWORD::::::::::::::::::::
  if (modo == "cambiarpass") {
    if (key) {
      entrada += key;
      Serial.println(entrada);

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        //lcd.print(key);
        lcd.print('*');
      }

      if (key == 'B') {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }

      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        if (entrada == pass) {
          repetirPass();
          modo = "repetirPass";
          key = '\0';
          entrada = "";
        } else {
          escribir("Error!", 5, 0);
          entrada = "";
          tone(5, 100, 1000);
          delay(1000);
          cambiarPass();
        }
      }

      if (key == 'D') {
        modo = "inicio";
        lcd.clear();
        lcd.print("DESACTIVADO");
      }


    }
  }



  //::::::::::::::::REPETIR PASSWORD::::::::::::::::::::
  if (modo == "repetirPass") {
    if (key) {
      entrada += key;
      Serial.println(entrada);

      if (key != 'A' and key != 'B' and key != 'C' and key != 'D') {
        //lcd.print(key);
        lcd.print('*');
      }

      if (key == 'B') {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        entrada = "";
      }

      if (key == 'A') {
        entrada = entrada.substring(0, entrada.length() - 1);
        pass = entrada;
        escribir("MODIFICADO", 3, 0);
        tone(5, 300, 500);
        delay(100);
        tone(5, 500, 500);
        delay(2000);
        escribir("DESACTIVADO", 0, 0);
        modo = "inicio";
      }

      if (key == 'D') {
        modo = "inicio";
        escribir("DESACTIVADO", 0, 0);
      }
    }
  }

}


void armar() {
  escribir("PASSWORD", 4, 0);
  lcd.setCursor(0, 1);
}

void desarmar() {
  escribir("PASSWORD", 4, 0);
  lcd.setCursor(0, 1);
}


void cambiarPass() {
  escribir("OLD PASSWORD", 2, 0);
  lcd.setCursor(0, 1);
}



void repetirPass() {
  escribir("NEW PASSWORD", 2, 0);
  lcd.setCursor(0, 1);
}


void activacion() {
  tone(5, 500, 1000);
  escribir("Activado en 1", 0, 0);
  delay(1500);
  tone(5, 500, 1000);
  escribir("Activado en 2", 0, 0);
  delay(1500);
  tone(5, 500, 1000);
  escribir("Activado en 3", 0, 0);
  delay(1500);
  tone(5, 500, 2000);
  delay(1000);
}



void escribir(String text, int col, int fila) {
  lcd.clear();
  lcd.setCursor(col, fila);
  lcd.print(text);
}
