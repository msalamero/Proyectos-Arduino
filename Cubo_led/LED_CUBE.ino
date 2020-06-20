//inicializando y declarando columnas de led
int columnas[16]={13,12,11,10,9,8,7,6,5,4,3,2,1,0,A5,A4};
//inicializando y declarando filas de leds
int filas[4]={A3,A2,A1,A0};

void setup(){
  //configurando columnas como salida
  for(int i = 0; i<16; i++){
    pinMode(columnas[i], OUTPUT);
  }
  //configurando filas como salida
  for(int i = 0; i<4; i++){
    pinMode(filas[i], OUTPUT);
  }
  //Ejecuta la funcion loop
  loop();
}

void loop(){
  apagarTodo();//apaga todo
  titilar();
  PrenderTodo();//prende todo
  delay(2000);
}

//apaga todo
void apagarTodo(){
  //apaga las columnas
  for(int i = 0; i<16; i++){
    digitalWrite(columnas[i], 1);
  }
  //apaga las filas
  for(int i = 0; i<4; i++){
    digitalWrite(filas[i], 0);
  }
}
 
//prende todo
void PrenderTodo(){
  //prende las columnas
  for(int i = 0; i<16; i++){
    digitalWrite(columnas[i], 0);
  }
  //prende las filas
  for(int i = 0; i<4; i++){
    digitalWrite(filas[i], 1);
  }
}

//con esto titilan los leds
void titilar(){
  int i = 150;
  while(i != 0){
    PrenderTodo();
    delay(i);
    apagarTodo();
    delay(i);
    i-= 5;
  }
}
