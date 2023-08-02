#include <AFMotor.h>
#include <Servo.h>

String command;
int trig = 4;
int echo = 3;
int tiempo;
int distancia;
bool Auto = false;

AF_DCMotor motor1(1);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo myservo;



void setup()
{
pinMode(4,OUTPUT);
pinMode(3,INPUT);
Serial.begin(9600);
myservo.attach(10);
myservo.write(90);
}

int Distancia(){
  digitalWrite(trig, HIGH);
  delay(800);
  digitalWrite(trig,LOW);
  tiempo = pulseIn(echo,HIGH);
  distancia = tiempo/58.2;
  return distancia;
}

void forward()
 {
  distancia = Distancia();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  //motor4.setSpeed(255);
  //motor4.run(FORWARD);
  if (distancia > 300){
    delay(500);
  }else{
    if(distancia > 200 && distancia < 300){
      delay(200);
    }else{
      delay(100);
    }
  }

  delay(1500);
  motor1.run(RELEASE);
  motor3.run(RELEASE);
  //motor4.run(RELEASE);
  
}

void backward()
 {
  //digitalWrite(5,HIGH);
  //digitalWrite(6,HIGH);
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  //motor4.setSpeed(255);
  //motor4.run(BACKWARD);
  delay(1500);
  //digitalWrite(5,LOW);
  //digitalWrite(6,LOW);
  motor1.run(RELEASE);
  motor3.run(RELEASE);
  //motor4.run(RELEASE);
}

void left()
 {
  //digitalWrite(6,HIGH);
  //digitalWrite(9,HIGH);
  myservo.write(180);
  distancia = Distancia();
  //digitalWrite(6,LOW);
  //digitalWrite(9,LOW);
  myservo.write(90);
  if(distancia > 64){
    //digitalWrite(6,HIGH);
    //digitalWrite(9,HIGH);
    motor3.setSpeed(255);
    motor3.run(BACKWARD);
    motor1.setSpeed(255);
    motor1.run(FORWARD);
    //digitalWrite(6,LOW);
    //digitalWrite(9,LOW);
    delay(1500);
    motor1.run(RELEASE);
    motor3.run(RELEASE);
    return;
  }

}

void right()
 {
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  myservo.write(0);
  delay(500);
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
  myservo.write(90);
  delay(500);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  if(distancia > 64){
    motor1.setSpeed(255);
    motor1.run(BACKWARD);
    motor3.setSpeed(255);
    motor3.run(FORWARD);
    //motor4.setSpeed(255);
    //motor4.run(FORWARD);
    digitalWrite(5,LOW);
    digitalWrite(8,HIGH);
    delay(1500);
    motor1.run(RELEASE);
    motor3.run(RELEASE);
  }
}

void Stop() 
{
  motor1.run(RELEASE);
  motor3.run(RELEASE);
  //motor4.run(RELEASE);
}

void Voz(String command)
{
  
   
}

void Automatico()
{
  if(Serial.available())
  {
    command = " ";
    command = Serial.readString();
    if(command == "S"){

      return;
    }  }   
  myservo.write(90);
    distancia = Distancia();
    Serial.println(distancia);
    if(distancia < 64)
    {
      Stop();
      myservo.write(180);
      distancia = Distancia();
      if(distancia > 64){
        left();
        delay(500);
        Automatico();
      }
      else{
        myservo.write(0);
        distancia = Distancia();
        if(distancia > 64){
          right();
          delay(500);
          //forward();
          Automatico(); 
        }
        else{
          backward();
          myservo.write(180);
          distancia = Distancia();
          if(distancia < 64){
            myservo.write(0);
            distancia = Distancia();
            if(distancia < 64){
              backward();
            }else{
              right();
              delay(500);
              Automatico();  
            }
          }else{
            left();
            delay(500);
            Automatico();            
          } 
        }
      }
    } else
    {
      forward();
    }
  Automatico();
}

void Manual(String command){

  if (command=="U"){
     forward();
  }
  if (command=="D"){
     backward();
  }
  if (command=="R"){
    right();
  }
    if (command=="L"){
    left();
  }
    if (command=="UL"){
    right();
  }
    if (command=="UR"){
    right();
  }
    if (command=="DL"){
    right();
  }
    if (command=="DR"){
    right();
  }
    if (command=="LON"){
    digitalWrite(7, HIGH);
  }
    if (command=="LOFF"){      
    digitalWrite(7, LOW);
  }
  if (command=="S"){
    motor1.run(RELEASE);
    motor3.run(RELEASE);
  }

}
void loop() 
{
    
 delay(10);

 while(Serial.available())
{
  command = " ";
  command = Serial.readString();
  if(command == "A"){

    Automatico();

  }else{      

     Manual(command);
  }
} 
  command = " ";
}