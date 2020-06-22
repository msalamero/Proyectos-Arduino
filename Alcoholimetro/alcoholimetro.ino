#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM900(52, 53);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
float mostrar;
void setup() {
lcd.begin(16, 2);
delay (100);
Serial.begin(9600);
// Inicializar el LCDint adc_MQ = analogRead(A0); //Lemos la salida analógica del MQ
float voltaje = adc_MQ * (5.0 / 1023.0); //Convertimos la lectura en un valor de voltaje
float Rs=1000*((5-voltaje)/voltaje); //Calculamos Rs con un RL de 1k
double alcohol=0.4091*pow(Rs/5463, -1.497); // calculamos la concentración de alcohol con la
ecuación obtenida.
mostrar = alcohol;
SIM900.begin(19200);
Serial.begin(19200);
SIM900.println("AT+CPIN=\"1867\"");
lcd.setCursor(0, 0);
lcd.print("OH: ");
lcd.setCursor(4,0);
lcd.print(mostrar);
lcd.setCursor(9,0);
lcd.print("mg/L");
if (mostrar>0.50){
lcd.setCursor(0, 1);
lcd.print("ALCOHOLIZADO");
mensaje_sms();
}
else {
lcd.setCursor(0, 1);
lcd.print("NO ALCOHOLIZADO");
}
}
void mensaje_sms(){
Serial.println("Enviando SMS...");
SIM900.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
delay(1000);
SIM900.println("AT+CMGS=\"3516879580\""); //Numero al que vamos a enviar el mensaje
delay(1000);
SIM900.println("La persona del que sos responsable, está alcoholizado.");// Texto del SMS
delay(100);
SIM900.println((char)26);//Comando de finalizacion ^Z
delay(100);
SIM900.println();
delay(5000); // Esperamos un tiempo para que envíe el SMS
Serial.println("SMS enviado");
}
void loop() {
}
