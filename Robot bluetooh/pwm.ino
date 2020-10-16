

int led = 9;           // pin de salida
int pulsador = 5;
int rele = 3;
bool rele_estado = 0;
int brillo = 0;    
int incremento = 50;
int pulsador_actual = 0;
int pulsador_anterior = 0;    

// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(led, OUTPUT); // se declara el pin como salida
  pinMode(pulsador, INPUT); // se declara el pin como entrada
  pinMode(rele, OUTPUT); // se declara el pin como salida
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("iniciando...");
  Serial2.print("conectado");
}

// the loop routine runs over and over again forever:
void loop() {

  if (Serial2.available()) {
    char dato = Serial2.read();
    Serial.print("nivel de brillo: ");
    

    switch(dato){
      case '0': brillo = 0;Serial.println(brillo);break;
      case '1': brillo = 50;Serial.println(brillo);break;
      case '2': brillo = 150;Serial.println(brillo);break;
      case '3': brillo = 200;Serial.println(brillo);break;
      case '+': brillo = brillo + incremento;Serial.println(brillo);break;
      case '-': brillo = brillo - incremento;Serial.println(brillo);break;
      case 'r':  rele_estado = !rele_estado;break;
     
      }
       Serial.println(brillo);
       Serial.println(rele_estado);
  }
    pulsador_actual = digitalRead(pulsador);
  
  if (pulsador_actual ==1){
    if(pulsador_anterior ==0) {
      brillo = brillo + incremento;
        rele_estado = !rele_estado;
        Serial.print("el valor del brillo es: ");
        Serial.println(brillo);
        Serial.print("estado del rele: ");
        Serial.println(rele_estado);
    }
    
 }
  pulsador_anterior = pulsador_actual;

  analogWrite(led, brillo); // entre 0 y  254 
  digitalWrite(rele, rele_estado);
  
  if (brillo >= 255) {
    brillo = 0;
  }

  delay(30);
   
}
