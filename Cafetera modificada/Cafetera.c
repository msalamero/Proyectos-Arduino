#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo_2;
Servo servo_3;

int relay = 13;

SoftwareSerial miBT(10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Listo");
  miBT.begin(9600);
  pinMode(relay, OUTPUT);
  servo_2.attach(2, 500, 2500);
  servo_3.attach(3, 500, 2500);
  servo_2.write(0);
  servo_3.write(0);
}

void loop() {
  if (miBT.available()) {
    char command = miBT.read();
    processCommand(command);
  }
}

void processCommand(char command) {
  switch (command) {
    case '1':
      activateServo1(servo_2);
      break;
    case '2':
      activateServo2(servo_3);
      break;
    case '3':
    activateRelay();
      break;
    default:
      break;
  }
}

void activateServo1(Servo& servo) {
  servo.write(90); // Mueve el servo a 90 grados
  delay(500);
  servo.write(0); // Vuelve a la posición inicial
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(0);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(0);
}
void activateServo2(Servo& servo) {
  servo.write(90); // Mueve el servo a 90 grados
  delay(1000);
  servo.write(0);
}
void activateRelay(){
  digitalWrite(relay, LOW);// Apaga el rele
  delay(500);
  digitalWrite(relay,HIGH);
  delay(500);
}
