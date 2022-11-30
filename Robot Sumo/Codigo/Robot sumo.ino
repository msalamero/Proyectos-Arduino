#include <AFMotor.h>    .

AF_DCMotor motor1(1);     
AF_DCMotor motor2(2);

int trigPin = 9;
int echoPin = 10;
int avanzar, Distancia;

void plusUltra() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  avanzar = pulseIn(echoPin, HIGH);
  Distancia =  avanzar / 58;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(5000);             // Espera 5 segs
  motor1.setSpeed(155);    // Velocidad de 255 (es la maxima)
  motor1.run(RELEASE);     
  motor2.setSpeed(155);    // Velocidad del 2 motor
  motor2.run(RELEASE);    

}

void loop() {
  plusUltra();
  if (Distancia > 1 && Distancia < 100) { // distancia entre el oponente y el sensor 
    motor1.run(BACKWARD);  //  va para atras y gira para buscar un oponente
    motor2.run(FORWARD);
    delay(300);
  } else {                 // pero si no encuentra un oponente
    motor1.run(FORWARD);   // Si esta entre esa distancia el robot va para adelante
    motor2.run(FORWARD);
    delay(300);
  }
}
