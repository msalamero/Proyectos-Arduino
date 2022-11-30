#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define PIN        6  
#define NUMPIXELS  151
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //define el objeto pixels que es la tira de leds

SoftwareSerial miBT1(10, 11);

void setup()
{
  Serial.begin(9600);
  pixels.begin();
  Serial.println("Listo");
  miBT1.begin(38400); //38400
}

void loop()
{
  if (miBT1.available())//Lee el moduloBT y envia a Arduino
  {
  Serial.write(miBT1.read());
  }
  int i = 0;
  int cantidad_de_vueltas = 0;
  int vueltas_hechas = 0;

//CONFIGURACION DE VUELTAS///////////////////////////////////////////////////////////////////////////////////

if(Serial.available()>0)
  {
    cantidad_de_vueltas=Serial.read();
    if(cantidad_de_vueltas=='1')
    {
      (cantidad_de_vueltas = 1);
    }
       if(cantidad_de_vueltas=='3')
    {
      (cantidad_de_vueltas = 3);
    }
    
       if(cantidad_de_vueltas=='5')
    {
      (cantidad_de_vueltas = 5);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// CÓDIGO PARA CUANDO SE HAN CONFIGURADO VUELTAS
  //COMANDOS PARA AVANZAR
  if(cantidad_de_vueltas != 0)
  {
    while(vueltas_hechas != cantidad_de_vueltas)
    {
         for(int a = 0; a < 2; a++)
         {
            if (miBT1.read() != -1)
            {
             Serial.println(miBT1.read());
             pixels.setPixelColor(i - 2, pixels.Color(0,0,0));
             pixels.setPixelColor(i - 1, pixels.Color(100,0,255));
             pixels.setPixelColor(i, pixels.Color(100,0,255));
             pixels.setPixelColor(i + 1, pixels.Color(100,0,255));
             pixels.show();
             i++;
             }
      
            if(a == 1)
            {
            a = a-1;
            }
         
            if(i == 152)
            {
             i = i-150;
             vueltas_hechas++;
             pixels.setPixelColor(151, pixels.Color(0,0,0));
                for(int x = 0; x < 152; x++)
                {
                  if(x != i)
                  {
                    pixels.setPixelColor(x-2, pixels.Color(0,255,0));
                    pixels.setPixelColor(x-1, pixels.Color(0,255,0));
                    pixels.setPixelColor(x, pixels.Color(0,255,0));
                    pixels.setPixelColor(x+1, pixels.Color(0,255,0));
                    pixels.setPixelColor(x+2, pixels.Color(0,255,0));
                    pixels.show();
                    pixels.setPixelColor(x-2, pixels.Color(0,0,0));
                    pixels.setPixelColor(x-1, pixels.Color(0,0,0));
                    pixels.setPixelColor(x, pixels.Color(0,0,0));
                    pixels.setPixelColor(x+1, pixels.Color(0,0,0));
                    pixels.setPixelColor(x+2, pixels.Color(0,0,0));
                    pixels.show();
                  }
                }   
            }
         }
    }
    if(vueltas_hechas == cantidad_de_vueltas)
    {
       for(int q = 0; q < 152; q++)
                {
                    pixels.setPixelColor(q, pixels.Color(255,0,255));
                    pixels.show();
                }   
    }
    
  }
  else
  {

        for(int a = 0; a < 2; a++)
        {
              if (miBT1.read() != -1)
              {
                 Serial.println(miBT1.read());
                 pixels.setPixelColor(i - 2, pixels.Color(0,0,0));
                 pixels.setPixelColor(i - 1, pixels.Color(255,0,0));
                 pixels.setPixelColor(i, pixels.Color(255,0,0));
                 pixels.setPixelColor(i + 1, pixels.Color(255,0,0));
                 pixels.show();
                 i++;
              }
  
                if(a == 1)
                {
                  a = a-1;
                }

                if(i == 152)
                {
                  i = i-150;
                  pixels.setPixelColor(151, pixels.Color(0,0,0));
                      for(int x = 0; x < 152; x++)
                      {
                          if(x != i)
                          {
                            pixels.setPixelColor(x-2, pixels.Color(0,255,0));
                            pixels.setPixelColor(x-1, pixels.Color(0,255,0));
                            pixels.setPixelColor(x, pixels.Color(0,255,0));
                            pixels.setPixelColor(x+1, pixels.Color(0,255,0));
                           pixels.setPixelColor(x+2, pixels.Color(0,255,0));
                           pixels.show();
                           pixels.setPixelColor(x-2, pixels.Color(0,0,0));
                           pixels.setPixelColor(x-1, pixels.Color(0,0,0));
                           pixels.setPixelColor(x, pixels.Color(0,0,0));
                           pixels.setPixelColor(x+1, pixels.Color(0,0,0));
                           pixels.setPixelColor(x+2, pixels.Color(0,0,0));
                           pixels.show();
                          }
                      }
                }  
      }
    
  }
//TERMINA AVANZAR
 if (Serial.available())
 miBT1.write(Serial.read()); //Lee Arduino y envia al moduloBT
}
