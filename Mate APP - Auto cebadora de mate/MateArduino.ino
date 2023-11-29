#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial sw(2,3);
char letra;
Servo miServo;  

int posicionInicial = 0;  
int posicionFinal = 90; 
int miRele = 8;  
int miRele2 = 7;
String encender="NO";

void setup(){ 
    lcd.init();
    lcd.backlight();

    miServo.attach(13);  
    miServo.write(posicionInicial); 
    delay(1000);
    pinMode(miRele,OUTPUT);  
    pinMode(miRele2,OUTPUT);
    sw.begin(9600);
   
}  

void mensajeinicio(){
  lcd.setCursor(0, 0);
   
  lcd.print("encendido: ");
  lcd.print(encender);
}

void loop(){ 
  
  mensajeinicio();
  
  if(sw.available())
      letra = sw.read(); 
  
  	
  if(letra=='A'){
    
    
      
    digitalWrite(miRele,HIGH);  
 	delay(1000);
    
    digitalWrite(miRele,LOW);
    if(encender=="NO"){
        lcd.clear();
  
        lcd.setCursor(3, 0);
   
        lcd.print("encendiendo");
    }
    else{
      lcd.clear();
  
      lcd.setCursor(3, 0);
   
      lcd.print("apagando");
    }
    for(int i=0;i<=13;i++){
       lcd.scrollDisplayLeft(); 
      delay(500);
    }  
    if(encender=="NO"){
      encender="SI";
    }
    else{
      encender="NO";
    } 
    letra='D'; 
    lcd.clear();        
  }
  if(letra=='B'){
    
    
   
    digitalWrite(miRele2,HIGH);  
 	delay(1000);
   
     
 
    digitalWrite(miRele2,LOW);   
    letra='D';
    lcd.clear();
  
  lcd.setCursor(2, 0);
   
  lcd.print("sirviendo agua!");
  for(int i=0;i<=13;i++){
       lcd.scrollDisplayLeft(); 
      delay(500);
    } 
    lcd.clear();        
  }
    if(letra=='C'){
 
 

  miServo.write(posicionFinal);  
     lcd.clear();
  
  lcd.setCursor(0, 0);
   
  lcd.print("sirviendo yerba!");
 for(int i=0;i<=15;i++){
       lcd.scrollDisplayLeft(); 
      delay(500);
    }
  
   
 
  miServo.write(posicionInicial); 
 
  lcd.clear();
   
  letra='D';

  } 
  if(letra=='E'){
    miServo.write(posicionInicial);
  }
  
}