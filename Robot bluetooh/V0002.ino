// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h> 

AF_DCMotor motor_DI(1);
AF_DCMotor motor_DD(2);
AF_DCMotor motor_TI(3);
AF_DCMotor motor_TD(4);

Servo servo1;
Servo servo2;
int posS1 = 90;    // variable to store the servo position 
int posS2 = 90;
int ang=0;
int i;
char c;
int motor,sentido,vel,cmd,mov;


char buf[10];
char v[20];
char recibiendo,pendiente=0;
char CR;          //contador caracteres recibidos

long tiempo;
int disparador = 50;   // triger
int eco = 22;      // echo
float distancia;
int avanzando;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Arduino listo");
  Serial1.begin(9600);

  pinMode(disparador, OUTPUT);
  pinMode(eco, INPUT);
  
  // turn on motor
  motor_DI.setSpeed(255); //max velocidad 255
  motor_DD.setSpeed(255); 
  motor_TI.setSpeed(255); 
  motor_TD.setSpeed(255);
  
  motor_DI.run(RELEASE);
  motor_DD.run(RELEASE);
  motor_TI.run(RELEASE);
  motor_TD.run(RELEASE);

  servo1.attach(9);
  servo2.attach(10);

   servo1.write(90);
   servo2.write(90);

    while(Serial1.available() > 0) {
    char t = Serial1.read();
  }
}


/**
 * 
 */
void loop() {


  if (Serial1.available())
    {  
        c = Serial1.read();
        //Serial.print("recibiendo...");
        if(c=='<')
        {
          CR=0;
          recibiendo=1;
        }
        else
        {
          v[CR]=c;
          CR++;
          if(c=='>')
          {
             pendiente=1;
             recibiendo=0;
          }
        }
     }

  if(pendiente==1)
  {
    Serial.println("dato pendiente");

    cmd= v[0] - 0x30;
    
    Serial.write(cmd+0x30);  

    switch(cmd)
    {
      case 0:       //Manejo independiente de motores 
         Serial.println("Motores");
        
        motor = v[1] - 0x30;
        vel= (v[3]- 0x30)*100+ (v[4]-0x30)*10 + (v[5] -0x30);
        sentido = v[7] - 0x30;
        Motores(motor,vel,sentido);
        sprintf(buf, "M:%d--Vel:%d--Sentido:%d",motor,vel,sentido);
        Serial.println(buf);
        break;

     case 1:      //mov predefinidos

        mov = v[2] - 0x30;
        vel= (v[4]- 0x30)*100+ (v[5]-0x30)*10 + (v[6] -0x30);
        //sprintf(buf, "mov:%d--Vel:%d",mov,vel);
        //Serial.println(buf);
         
        switch(mov)
        {
         
            case 0:       //Pare
              Motores(1,0,0);
              Motores(2,0,0);
              Motores(3,0,0);
              Motores(4,0,0); 
              Serial.println("Pare"); 
              avanzando = 0;        
              break;

            case 1:       //Avance
              Motores(1,vel,1);
              Motores(2,vel,1);
              Motores(3,vel,1);
              Motores(4,vel,1); 
              Serial.println("\nAvance");
              avanzando = 1;           
              break;
              
            case 2:       //Retroceda
              Motores(1,vel,0);
              Motores(2,vel,0);
              Motores(3,vel,0);
              Motores(4,vel,0);
              Serial.println("\nRetroceda");
              avanzando = 0;            
              break;

              
            case 3:       //Derecha
              Motores(1,vel,1);
              Motores(4,vel,1);
              Motores(2,vel,0);
              Motores(3,vel,0);  
              Serial.println("\nDerecha");
              avanzando = 0;          
              break;

              
            case 4:       //IZQ
              Motores(2,vel,1);
              Motores(3,vel,1);
              Motores(1,vel,0);
              Motores(4,vel,0);   
              Serial.println("\nIzquierda");
              avanzando = 0;         
              break;
        }
        break;

      case 2: // MOV PREDEFINIDOS DE CAMARA

          mov = v[2] - 0x30;
          switch(mov)
          {
            case 0: //Centrar
                Serial.println("CAM CENTRADA!!");
                posS2 =90 ;
                posS1 =90 ;
                servo2.write(posS2);
                servo1.write(posS1);
                break;
            
            case 1: //Arriba
                Serial.println("CAM ARRIBA!!");
                posS1 += 10;
                if(posS1 > 180)
                { posS1=100;
                }
                servo1.write(posS1);
                break;
            case 2: //Abajo
                Serial.println("CAM ABAJO!!");
                posS1 -= 10;
                if(posS1 < 0)
                { posS1=0;
                }
                servo1.write(posS1);
                break;
            case 3: //IZQ
                Serial.println("CAM IZQUIERDA!!");
                posS2 += 10;
                if(posS2 > 100)
                { posS2=100;
                }
                servo2.write(posS2);
                break;
            case 4: //Der
                Serial.println("CAM DERECHA!!");
                posS2 -= 10;
                if(posS2 < 0)
                { posS2=0;
                }
                servo2.write(posS2);
                break;

            
           }
           break;
 
      case 3: // MOV  DE servos manuales

      
          mov = v[2] - 0x30;
          ang= (v[4]- 0x30)*100+ (v[5]-0x30)*10 + (v[6] -0x30);
          switch(mov)
          {
            case 1:
              posS1 = ang;
              servo1.write(posS1);
              break;

            case 2:
              posS2 = ang;
              servo2.write(posS2);
              break;
          }
     
    }

       
    
    pendiente=0;

  }


  // lanzamos un pequeño pulso para activar el sensor
 digitalWrite(disparador, HIGH);
 delayMicroseconds(10);
 digitalWrite(disparador, LOW);
//  
//  // medimos el pulso de respuesta
  tiempo = pulseIn(eco, HIGH); // dividido por 2 por que es el 
//                                       // tiempo que el sonido tarda
//                                       // en ir y en volver
//  // ahora calcularemos la distancia en cm
//  // sabiendo que el espacio es igual a la velocidad por el tiempo
//  // y que la velocidad del sonido es de 343m/s y que el tiempo lo 
//  // tenemos en millonesimas de segundo
 distancia = tiempo /29 / 2;
// Serial.println(distancia);
  
  if ( distancia <= 20)
  {

              Motores(1,0,0);
              Motores(2,0,0);
              Motores(3,0,0);
              Motores(4,0,0); 
              Serial.println("Parada emergencia");     
  }

     
    }



void Motores(int Nmotor, int Vel , int sentido)
{
  switch(Nmotor)
  {
    case 1:
      motor_DI.setSpeed(Vel);
      if(sentido)
        motor_DI.run(FORWARD);
      else 
        motor_DI.run(BACKWARD);
      break;

    case 2:
      motor_DD.setSpeed(Vel);
      if(sentido)
        motor_DD.run(FORWARD);
      else 
        motor_DD.run(BACKWARD);
      break;

    case 3:
      motor_TI.setSpeed(Vel);
      if(sentido)
        motor_TI.run(FORWARD);
      else 
        motor_TI.run(BACKWARD);
      break;

    case 4:
      motor_TD.setSpeed(Vel);
      if(sentido)
        motor_TD.run(FORWARD);
      else 
        motor_TD.run(BACKWARD);
      break;
     
      
  }
  
}


  /*
  uint8_t i;
  
  Serial.print("\nMotor delantero Izquierdo");

  Serial.print("\nADELANTE");
  Serial.print("\nACELERANDO.....");
  motor_TI.run(FORWARD);
  for (i=0; i<255; i++) {
    servo1.write(i);
    motor_TI.setSpeed(i);  
    delay(10);
 }
   Serial.print("DESACELERANDO....");
  for (i=255; i!=0; i--) {
    servo1.write(i-255);
    motor_TI.setSpeed(i);  
    delay(10);
 }
  
  Serial.print("\nATRAS");
  Serial.print("\nACELERANDO.....");

  motor_TI.run(BACKWARD);
  for (i=0; i<255; i++) {
    servo1.write(i);
    motor_TI.setSpeed(i);  
    delay(10);
 }
    Serial.print("DESACELERANDO....");
  for (i=255; i!=0; i--) {
    servo1.write(i-255);
    motor_TI.setSpeed(i);  
    delay(10);
 }
  

  Serial.print("LISTO");
  motor_TI.run(RELEASE);
  delay(1000);
}*/
