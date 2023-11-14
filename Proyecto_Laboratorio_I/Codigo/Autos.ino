//info[0]=adelante o atras
//info[1]=derecha o izquierda
//info[2]=luces
int integerValue = 255;
byte info[3];
 
 #include <AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  Serial.begin(9600);
}
 
void loop()
{
  if(Serial.available() > 0){
    Serial.readBytes(info, 3);
    //adelante
    if(info[0]==(byte)2){
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(integerValue);
      motor2.setSpeed(integerValue);
    }
    //quieto
    if(info[0]==(byte)0){
     motor1.setSpeed(0);
    motor2.setSpeed(0);
    }
    //atras
    if(info[0]==(byte)1){
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor1.setSpeed(integerValue);
      motor2.setSpeed(integerValue);
    }
 
    //derecha
    if(info[1]==(byte)2){
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(integerValue);
      motor2.setSpeed(integerValue);
    }
    //no gira
    /*if(info[1]==(byte)0){
     motor1.setSpeed(0);
     motor2.setSpeed(0);
    }
    //izquierda
    */
    if(info[1]==(byte)1){
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor1.setSpeed(integerValue);
      motor2.setSpeed(integerValue);
    }
    //Luces
    if(info[2]==(byte)1){
      digitalWrite(8, HIGH);
    }
    else{
      digitalWrite(8, LOW);
    }
  }
}