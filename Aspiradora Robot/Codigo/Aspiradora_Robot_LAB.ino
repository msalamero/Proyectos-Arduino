//Pines motor 1 IZQ
#define fw1 12
#define bk1 11

//pines motor 2 DER
#define fw2 10
#define bk2 9

//pin sensor ultrasonico
#define echo_fw 2
#define trig_fw 3
#define echo_L 5
#define trig_L 4
#define echo_R 6
#define trig_R 7

//pin ventilador
#define fan 8

int speed=150;
int umbral = 30;
int dist_fw = 0;//distancia en centimetros
int dist_R = 0;
int dist_L = 0;

//bandera
char modo[6]={'0','0','0','0','0','0'};

void setup() {
  // put your setup code here, to run once:
    //Motor 1
  pinMode(fw1,OUTPUT);//FW
  pinMode(bk1,OUTPUT);//BK
  
  //Motor 2
  pinMode(fw2,OUTPUT);//FW
  pinMode(bk2,OUTPUT);//BK
  
  //ventilador
  pinMode(fan, OUTPUT);
  
  Serial.begin(38400);
  Serial3.begin(38400);
}


void loop()
{

  if(modo[0]=='1'){

    //configura distancia y velocidad segun lo recibido por BT
    umbral = configBT(1,modo[1]);
    speed = configBT(4,modo[4]);
    
    //aspira al iniciar el modo automatico
    aspirar(modo[5]);

    //arranca
    if(modo[5] == '1'){
      
      //lee la distancia en cm
      dist_fw = 0.01723 * readUltrasonicDistance(trig_fw,echo_fw);

      //envia por BT la distancia
      Serial3.print(dist_fw);

      //si la dist es mayor a 100
      //mueve el carro hacia adelante por 1 seg
      if(dist_fw > umbral){
        move();
      }
      //sino...
      else{
        
        //frena el carro
        stop();
        
        //mide las distancias de los costados
        dist_R = 0.01723 * readUltrasonicDistance(trig_R,echo_R);
        dist_L = 0.01723 * readUltrasonicDistance(trig_L,echo_L);
        
        if(dist_R > dist_L){
          rotate('r');
          delay(50);
        }
        else if(dist_R < dist_L){
          rotate('l');
          delay(50);
        }
        else{
          moveBack();
        }
        
      }
    }
    else{
      stop();
    }

  }
  else if(modo[0]=='0'){

    speed = 100;
    
    //prende o apaga el ventilador
    aspirar(modo[5]);
    
    //se mueve en la direccion del boton que se aprieta
    if(modo[1]=='1')
      move();
    else if(modo[2]=='1')
      moveBack();
    else if(modo[3]=='1')
      rotate('r');
    else if(modo[4]=='1')
      rotate('l');
    else
      stop();
    
  }
  
  if(Serial3.available()){
    Serial3.readBytes(modo,6);
    //Serial.println(modo);
  }
  delay(100);
}



//segun el indice devuelve un valor para configuracion
//si el index es 1 devuelve un valor para distancia
//sino devuelve un valor para velocidad
int configBT(int index, char config){
  int valor;
  switch(config){
    case '1'://baja
      valor = index == 1 ? 10 : 90;
    break;
    case '2'://media
      valor = index == 1 ? 20 : 110;
    break;
    case '3'://alta
      valor = index == 1 ? 30 : 140;
    break;
  }
  return valor;
}
void aspirar(char modo){
  if(modo=='1')
  digitalWrite(fan,HIGH);
  else if(modo=='0')
  digitalWrite(fan,LOW);
}

//mueve el carro hacia adelante
void move()
{
  //rueda derecha
  analogWrite(fw1, speed);
  digitalWrite(bk1, LOW);
  //rueda izquierda
  analogWrite(fw2, speed);
  digitalWrite(bk2, LOW);
}


//mueve el carro hacia atras
void moveBack()
{
  //rueda derecha
  digitalWrite(fw1, LOW);
  analogWrite(bk1, speed);

  //rueda izquierda
  digitalWrite(fw2, LOW);
  analogWrite(bk2, speed);
}

//mueve la rueda hacia adelante o hacia atras
//si el primer parametro es el pin fw mueve hacia adelante
//si el primer parametro es el pin bk mueve hacia atras
void move(int fw, int bk)
{
  analogWrite(fw, speed);
  digitalWrite(bk, LOW);
}

//Gira el carro en una direccion
void rotate(char dir)
{
  if(dir=='r')
  {
    move(fw1,bk1);//rueda de la izquierda hacia adelante
    move(bk2,fw2);//detiene la rueda de la derecha
  }
  else if(dir=='l')
  {
    move(fw2,bk2);//rueda de la derecha hacia adelante
    move(bk1,fw1);//detiene la rueda de la izquierda
  }
}

//detiene el carro
void stop()
{
  digitalWrite(fw1, LOW);
  digitalWrite(bk1, LOW);
  digitalWrite(fw2, LOW);
  digitalWrite(bk2, LOW);
}

//frena una sola rueda
void stop(int fw, int bk)
{
  digitalWrite(fw, LOW);
  digitalWrite(bk, LOW);
}

//emite y lee el pulso sonico para la medir la distancia
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
