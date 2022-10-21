#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);

#define RST_PIN  5       //Pin 9 para el reset del RC522
#define SS_PIN_ENB  53   //Pin 10 para el SS (SDA) del RC522
MFRC522 MyLectorRF(SS_PIN_ENB, RST_PIN); //Creamos el objeto para el RC522

boolean x=false;

String BufferID = "";
String TarjetaOk = "b9b46a8e";
String TarjetaOk2 = "c79bb75f";
String TarjetaOk3 = "29fcafc1";
String TarjetaOk4 = "bd2c83a6";

 
void setup() {
  Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  MyLectorRF.PCD_Init(); // Iniciamos  el MyLectorRF
  Serial.println("Control Inicializado ...");

  lcd.init();  
  lcd.backlight();

  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
 

}

void loop() 
{

  
  // Verifica si se ha detectado alguna tarjeta
  if ( MyLectorRF.PICC_IsNewCardPresent()) 
  {  
      // Determina el codigo de la tarjeta
            if ( MyLectorRF.PICC_ReadCardSerial()) 
            {
                  // Recupera en ID de la Tarjeta
                  BufferID = "";
                  //Serial.print("Card UID:");
                  for (byte i = 0; i < MyLectorRF.uid.size; i++) 
                  {
                          //Serial.print(MyLectorRF.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          //Serial.print(MyLectorRF.uid.uidByte[i], HEX);
                          BufferID = BufferID + String(MyLectorRF.uid.uidByte[i], HEX);
                  } 
                  
                  //Serial.println();
                  //Serial.println(BufferID);

                  
           
                   if (BufferID == TarjetaOk)
                  {
                    Serial.println("Puede Ingresar ...");
                    Serial.println ("Abriendo puerta");
                    lcd.setCursor(1,0);
                    lcd.print("Puede Ingresar ...");
                    
                  }
                   else if (BufferID == TarjetaOk2)
                  {
                    Serial.println("Puede Ingresar ...");
                    Serial.println ("Abriendo puerta");
                    lcd.setCursor(1,0);
                    lcd.print("Puede Ingresar ...");
                   
                  }
                   else if (BufferID == TarjetaOk3)
                  {
                    Serial.println("Puede Ingresar ...");
                    Serial.println ("Abriendo puerta");
                    lcd.setCursor(1,0);
                    lcd.print("Puede Ingresar ...");
                   
                  }
                  else if (BufferID == TarjetaOk4)
                  {
                    Serial.println("Puede Ingresar ...");
                    Serial.println ("Abriendo puerta");
                    lcd.setCursor(1,0);
                    lcd.print("Puede Ingresar ...");
                    
                    
                  }
                  else
                  {
                    Serial.println("Tarjeta Invalida ...");
                    lcd.print("Tarjeta Invalida");
                  }
                  delay(3000);
                  lcd.clear();

                  // Terminamos la lectura de la tarjeta  actual
                  MyLectorRF.PICC_HaltA();         
            }  
  }
                
  int valor=digitalRead(3);
  
  Serial.print("Push:");
  Serial.print(valor);
  delay(4000);
  
  if(valor==1){
    x=!x;
  }
  
  if(x){
    digitalWrite(2,HIGH);
  }
  
  else{
    digitalWrite(2,LOW);
  }
  
  delay(5000);           
     
  
  } 
