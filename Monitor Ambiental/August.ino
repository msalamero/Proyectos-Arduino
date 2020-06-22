int uwu=1;
char dato;
// Temperatura y Humedad
int DHpin = 2;
byte dat [5];
// Ultrasonico
const int trigPin = 3;
const int echoPin = 4;
long duration;
int distance;
// MQ-7
const int AOUTpin = A0; //the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
const int DOUTpin = 5; //the DOUT pin of the CO sensor goes into digital pin D8 of the arduino
int limit;
int value;
// MQ-5
int sensord=6;
int gas_valued;
float sensora=A1;
float gas_valuea;
// MQ-2
int smokeA0 = A2;
int smokeD0 = 7;
// Your threshold value
int sensorThres = 400;
// LED RGB
int redpin = 9; //select the pin for the red LED
int bluepin = 10; // select the pin for the  blue LED
int greenpin = 8;// select the pin for the green LED
int val = 0;
// Fotosensor
int sensorPin = A3; //define analog pin 9
int valuex = 0;
//Fuego
int digitalPin = 11; // KY-026 digital interface
int analogPin = A4; // KY-026 analog interface
int digitalVal; // digital readings
int analogVal; //analog readings
// Musica
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
// change this to make the song slower or faster
int tempo = 108;
// change this to whichever pin you want to use
int buzzer = 12;
int melody[] = {

  NOTE_E4, 2, NOTE_G4, 4,
  NOTE_D4, 2, NOTE_C4, 8, NOTE_D4, 8,
  NOTE_E4, 2, NOTE_G4, 4,
  NOTE_D4, -2,
  NOTE_E4, 2, NOTE_G4, 4,
  NOTE_D5, 2, NOTE_C5, 4,
  NOTE_G4, 2, NOTE_F4, 8, NOTE_E4, 8,
  NOTE_D4, -2,
  NOTE_E4, 2, NOTE_G4, 4,
  NOTE_D4, 2, NOTE_C4, 8, NOTE_D4, 8,
  NOTE_E4, 2, NOTE_G4, 4,
  NOTE_D4, -2,
  NOTE_E4, 2, NOTE_G4, 4,

  NOTE_D5, 2, NOTE_C5, 4,
  NOTE_G4, 2, NOTE_F4, 8, NOTE_E4, 8,
  NOTE_F4, 8, NOTE_E4, 8, NOTE_C4, 2,
  NOTE_F4, 2, NOTE_E4, 8, NOTE_D4, 8,
  NOTE_E4, 8, NOTE_D4, 8, NOTE_A3, 2,
  NOTE_G4, 2, NOTE_F4, 8, NOTE_E4, 8,
  NOTE_F4, 8, NOTE_E4, 8, NOTE_C4, 4, NOTE_F4, 4,
  NOTE_C5, -2,

};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

byte read_data ()
{
  byte data;
  for (int i = 0; i < 8; i ++)
  {
    if (digitalRead (DHpin) == LOW)
    {
      while (digitalRead (DHpin) == LOW); // wait for 50us
      delayMicroseconds (30); // determine the duration of the high level to determine the data is '0 'or '1'
      if (digitalRead (DHpin) == HIGH)
        data |= (1 << (7 - i)); // high front and low in the post
      while (digitalRead (DHpin) == HIGH); // data '1 ', wait for the next one receiver
    }
  }
  return data;
}

void start_test ()
{
  digitalWrite (DHpin, LOW); // bus down, send start signal
  delay (30); // delay greater than 18ms, so DHT11 start signal can be detected

  digitalWrite (DHpin, HIGH);
  delayMicroseconds (40); // Wait for DHT11 response

  pinMode (DHpin, INPUT);
  while (digitalRead (DHpin) == HIGH);
  delayMicroseconds (80); // DHT11 response, pulled the bus 80us
  if (digitalRead (DHpin) == LOW);
  delayMicroseconds (80); // DHT11 80us after the bus pulled to start sending data

  for (int i = 0; i < 4; i ++) // receive temperature and humidity data, the parity bit is not considered
    dat[i] = read_data ();

  pinMode (DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
}


void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(DHpin, OUTPUT);
  pinMode(DOUTpin, INPUT);  //sets the pin as an input to the arduino
  //pinMode(ledPin, OUTPUT);  //sets the pin as an output of the arduino
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  //pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  pinMode(sensord,INPUT);
  pinMode(sensora,INPUT);
  pinMode(smokeA0, INPUT);
  pinMode(smokeD0, INPUT);
  Serial.begin(9600); // Starts the serial communication
}
void Temp()
{
  start_test();
  Serial.print("Humdity = ");
  Serial.print(dat[0], DEC); //Displays the integer bits of humidity;
  Serial.print('.');
  Serial.print(dat[1], DEC); //Displays the decimal places of the humidity;
  Serial.println('%');
  Serial.print("Temperature = ");
  Serial.print(dat[2], DEC); //Displays the integer bits of temperature;
  Serial.print('.');
  Serial.print(dat[3], DEC); //Displays the decimal places of the temperature;
  Serial.println('C');
  delay(1000);
}
void Distancia ()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("DISTANCIA\n");
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance < 30)
  {
    Serial.print("ALGO ESTA CERCA (AZUL)\n");
    setColor(0, 0, 255);  // blue
    //delay(3000);
    //setColor(0, 0, 0);  
  }
  else
  {
    Serial.print("DESPEJADO (VERDE)\n");
    setColor(0, 255, 0);  
    //delay(3000);
    //setColor(0, 0, 0); 
  }
}
void MQ7 ()
{
  value = analogRead(AOUTpin); //reads the analaog value from the CO sensor’s AOUT pin
  limit = digitalRead(DOUTpin); //reads the digital value from the CO sensor’s DOUT pin
  Serial.print("MQ-7\n");
  Serial.print("CO value: ");
  Serial.println(value);  //prints the CO value
  Serial.print("Deteccion: ");
  Serial.print(limit);  //prints the limit reached as either LOW or HIGH (above or underneath)
  Serial.print("\n");
  delay(1000);
  if (limit == HIGH) {
    Serial.print("HAY MONOXIDO DE CARBONO WEY(ROJO)\n");
    setColor(255, 0, 0);  // red
    //delay(3000);
    //setColor(0, 0, 0);  
  }
  else {
    Serial.print("NO HAY MONOXIDO DE CARBONO WEY(VIOLETA)\n");
    setColor(255, 0, 255); // purple
    //delay(3000);
    //setColor(0, 0, 0);  
  }
}
void MQ5 ()
{
  Serial.print("MQ-5\n");
  gas_valued=digitalRead(sensord);
  Serial.print("Deteccion: ");
  Serial.println(gas_valued);
  gas_valuea=analogRead(sensora);
  Serial.print("Valor de Gas Natural: ");
  Serial.println(gas_valuea);
  if (gas_valued == HIGH) {
    Serial.print("HAY GAS NATURAL (AMARILLO)\n");
    setColor(255, 255, 0);  // yellow
    //delay(3000);
    //setColor(0, 0, 0);  
  }
  else {
    Serial.print("NO HAY GAS NATURAL (CELESTE)\n");
    setColor(0, 255, 255);  // aqua
    //delay(3000);
    //setColor(0, 0, 0);  
  }
}
void MQ2 ()
{
 int analogSensor = analogRead(smokeA0);
 int digitalSensor = digitalRead(smokeD0);
 Serial.print("MQ-2\n");
  Serial.print("Nivel de Humo: ");
  Serial.println(analogSensor);
  Serial.print("Deteccion: ");
  Serial.println(digitalSensor);
  // Checks if it has reached the threshold value
  if (digitalSensor == HIGH)
  {
    Serial.print("HAY HUMO (VERDE)\n");
    setColor(0, 255, 0);  // green
    //delay(3000);
    //setColor(0, 0, 0);
  }
  else
  {
    Serial.print("HAY HUMO (AZUL)\n");
    setColor(0, 0, 255);  // red
    //delay(3000);
    //setColor(0, 0, 0);
  }
  delay(100);
}
void LED ()
{
  Serial.print("LED\n");
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);
  setColor(255, 0, 255); // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);
  setColor(0, 0, 0);  // nedaaaah
  delay(1000);
}
void Luz ()
{
  valuex = analogRead(sensorPin);
  Serial.print("LUZ\n");
  Serial.print("Nivel de Luz = ");
  Serial.println(valuex, DEC); // light intensity
  if (valuex > 300) // low values for dark environment
  {
    Serial.print("Esta Oscuro (CELESTE)\n");
    setColor(0, 255, 255);  // aqua
    //delay(3000);
    //setColor(0, 0, 0); 
  }
  else
  {
    Serial.print("Hay Luz (AMARILLO)\n");
    setColor(255,255,0);  // yellow
    //delay(3000);
    //setColor(0, 0, 0); 
  }
  // high values for bright environment
}
void Fuego ()
{
  // Read the digital interface
  digitalVal = digitalRead(digitalPin);
  analogVal = analogRead(analogPin);
  Serial.print("FUEGO\n");
  Serial.print("Nivel de Fuego = ");
  Serial.println(analogVal); // print analog value to serial
  if (digitalVal == HIGH) // if flame is detected
  {
    Serial.print("FUEGO DETECTADO (ROJO)\n");
    setColor(255, 0, 0);  // red
    //delay(3000);
    //setColor(0, 0, 0); // limpia
  }
  else
  {
    Serial.print("FUEGO NO DETECTADO (VIOLETA)\n");
    setColor(255, 0, 255); // purple
    //delay(3000);
    //setColor(0, 0, 0); // limpia
  } 
}
void loop()
{
  if (uwu==1)
  {    
    Serial.print("1)Sensor de Distancia\n");
    Serial.print("2)Sensor de Monoxido de Carbono (MQ7)\n");
    Serial.print("3)Sensor de Gas Natural (MQ5)\n");
    Serial.print("4)Sensor de Humo (MQ2)\n");
    Serial.print("5)Sensor de Luz\n");
    Serial.print("6)Sensor de Fuego\n");
    Serial.print("7)Musiquita\n");
    Serial.print("8)Apagar LED\n");
    Serial.print("Ingrese la opcion deseada:\n");
  }
  dato=Serial.read();
  uwu=0;
  switch (dato)
  {
    case '1':
      Distancia ();
      //delay(2000);
      dato='0';
    break;
    case '2':
      MQ7 ();
      //delay(2000);
      dato='0';
    break;
    case '3':
      MQ5 ();
      //delay(2000);
      dato='0';
    break;
    case '4':
      MQ2 ();
      //delay(2000);
      dato='0';
    break;
    case '5':
       Luz ();
       //delay(2000);
       dato='0';
    break;
    case '6':
      Fuego ();
      //delay(2000);
      dato='0';
    break;
    case '7':
      Musica ();
      //delay(2000);
      dato='0';
    break;
    case '8':
      Serial.print("LED OFF\n");
      setColor(0, 0, 0); // limpia
      //delay(2000);
      dato='0';
    break;
    default:
      //Serial.print("No ingreso una opcion valida...\n");
      //delay(2000);
      
    break;
  }
}
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redpin, red);
  analogWrite(greenpin, green);
  analogWrite(bluepin, blue);
}
void Musica()
{
  Serial.print("MUSICA\n");
  setColor(0, 255, 0);  // green
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}
