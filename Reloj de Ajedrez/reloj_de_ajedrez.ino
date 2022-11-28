#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_main(0x27, 16, 2);
LiquidCrystal_I2C lcd_secondary(0x26, 16, 2);

String msg[3] = {"", "", ""};
char cmd;
bool recieving = false;
bool check = false;
int ctr = 0;
int i = 0;

bool is_game_on = false;
bool is_config_ready = false;
bool p1_turn = false;
bool p2_turn = false;
unsigned long start_time;
short int winner = 0;
String p1_name = "";
String p2_name = "";
long int p1_sec = 0;
long int p2_sec = 0;

unsigned long last_delta_1 = 0;
unsigned long delta_time_1 = 0;
unsigned long curr_time_1 = 0;
unsigned long turn_start_time_1 = 0;

unsigned long last_delta_2 = 0;
unsigned long delta_time_2 = 0;
unsigned long curr_time_2 = 0;
unsigned long turn_start_time_2 = 0;

String get_player_time_str(String display){
  unsigned long msec = 0; 
  if (display == "p1")
    msec = p1_sec;
  if (display == "p2")
    msec = p2_sec;
  String fmt_time = "";
  String s_mins = "";
  String s_secs = "";
  unsigned long mins =msec/60000;
  unsigned long sec = (msec/1000)%60;
  if (mins >= 10) s_mins = String(mins);
  if (mins < 10) s_mins = "0" + String(mins);
  if (sec > 10) s_secs = String(sec);
  if (sec < 10) s_secs = "0" + String(sec);
  fmt_time = s_mins + ":" + s_secs;
  return fmt_time;
}

void setup()
{
  lcd_main.begin();
  lcd_main.backlight();
  lcd_secondary.begin();
  lcd_secondary.backlight();
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {

  if (!is_game_on){
    
    if (Serial.available()){
      cmd = Serial.read();
      if (cmd == '>'){
        recieving = false;
        p1_name = msg[0];
        p2_name = msg[1];
        p1_sec = msg[2].toInt() * 60000;
        p2_sec = msg[2].toInt() * 60000;
        is_config_ready = true;
        recieving = false;
      }
      if (recieving) {
        if (cmd == ',')
          i++;
      }
      if (recieving) {
        if (cmd != ','){
          msg[i] += cmd;
          ctr++;
        }
      }
      if (cmd == '<'){
        recieving = true;
        ctr = 0;
        i = 0;
        msg[0] = "";
        msg[1] = "";
        msg[2] = "";
      }
    }

    if (winner == 0 && is_config_ready == false){
      lcd_secondary.setCursor(0, 0);
      lcd_secondary.print("Reloj de Ajedrez");
      lcd_secondary.setCursor(0, 1);
      lcd_secondary.print(" Pulse 'Jugar'! ");
      lcd_main.setCursor(0, 0);
      lcd_main.print("   Esperando    ");
      lcd_main.setCursor(0, 1);
      lcd_main.print("Configuracion...");
    }

    if (winner == 0 && is_config_ready == true){
      lcd_main.setCursor(0, 0);
      lcd_main.print(" Configuracion  ");
      lcd_main.setCursor(0, 1);
      lcd_main.print("   Recibida!    ");
      lcd_secondary.setCursor(0, 0);
      lcd_secondary.print(" Toque un boton ");
      lcd_secondary.setCursor(0, 1);
      lcd_secondary.print(" para comenzar! ");
      
      if (digitalRead(6)) {
        is_game_on = true; 
        start_time = abs(0-millis());
        Serial.println(3);
        p1_turn = false;
        p2_turn = true;
      }
      if (digitalRead(7)) {
        is_game_on = true; 
        start_time = abs(0-millis());
        Serial.println(3);
        p1_turn = true;
        p2_turn = false;
      }
    }

    if (winner != 0){
      lcd_secondary.setCursor(0, 0);
      lcd_secondary.print(msg[winner - 1] + " ganador!");
      lcd_secondary.setCursor(0, 1);
      lcd_secondary.print("       :D       ");
      if (digitalRead(6) || digitalRead(7)) {
        msg[0] = "";
        msg[1] = "";
        winner = 0;
      }
    }
    delay(50);
  }

  if (is_game_on) {
    String p1_time = get_player_time_str("p1");
    String p2_time = get_player_time_str("p2");
    lcd_main.setCursor(0, 0);
    lcd_main.print("Jugador 1: " + p1_time);
    lcd_main.setCursor(0, 12);
    lcd_main.print("Jugador 2: " + p2_time);
    if (digitalRead(7)) {
      if (p1_turn == false){
        turn_start_time_1 = millis();
        p1_turn = true;
        p2_turn = false;
        delta_time_1 = 0;
        curr_time_1 = 0;
        Serial.println(2);
      }
    }
    if (digitalRead(6)) {
      if (p2_turn == false){
        turn_start_time_2 = millis();
        p1_turn = false;
        p2_turn = true;
        delta_time_2 = 0;
        curr_time_2 = 0;
        Serial.println(1);
      }
    }
    if (p1_turn) {
      curr_time_1 = millis();
      last_delta_1 = delta_time_1;
      delta_time_1 = curr_time_1 - (turn_start_time_1 - start_time);
      if (last_delta_1 != 0 && (delta_time_1 - last_delta_1) < 1000){
        p1_sec = p1_sec - (delta_time_1 - last_delta_1);
      }
      if (p1_sec <= 0){
        winner = 2;
        is_game_on = false;
        is_config_ready = false;
        p1_sec = 0;
        msg[2] = "";
        p1_sec = 0;
        p2_sec = 0;
        lcd_secondary.clear();
        Serial.println(5);
      }
    }
    if (p2_turn) {
      curr_time_2 = millis();
      last_delta_2 = delta_time_2;
      delta_time_2 = curr_time_2 - (turn_start_time_2 - start_time);
      if (last_delta_2 != 0 && (delta_time_2 - last_delta_2) < 1000){
        p2_sec = p2_sec - (delta_time_2 - last_delta_2);
      }
      if (p2_sec <= 0){
        winner = 1;
        is_game_on = false;
        is_config_ready = false;
        p2_sec = 0;
        msg[2] = "";
        p1_sec = 0;
        p2_sec = 0;
        lcd_secondary.clear();
        Serial.println(5);
      }
    }

    if (Serial.available()){
      cmd = Serial.read();
      if (cmd == '8'){
        is_game_on = false;
        is_config_ready = false;
        p1_sec = 0;
        p2_sec = 0;
        msg[2] = "";
        lcd_secondary.clear();
        Serial.println(5);
      }
    }

    delay(100);
  }
}
