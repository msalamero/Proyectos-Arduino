# Proyecto ArduinoRacing22K

## Antecedentes

Originalmente se nos habían ocurrido ideas significativamente diferentes a la que terminamos desarrollando, tales como una tostadora que escriba y/o dibuje en una tostada, un sistema de riego automático, un sistema para alimentar mascotas automático, un guante que escriba en una aplicación el significado de diferentes gestos que se hacían en lenguaje para mudos, entre otras ideas. Pero finalmente, luego de considerar que algunas de esas ideas eran muy difíciles de hacer y otras eran demasiado simples o muy vistas anteriormente, decidimos hacer algo que no necesariamente tuviera un fin útil en la vida diaria, sino que sirviera para divertirse. Fue así como se nos ocurrió la idea de hacer una versión con arduinos de las antiguas pistas de carreras de juguete, en las cual los vehículos se controlaban mediante un control remoto.

![](/imagenes/1.png)

## Propuesta mejorada

Nuestra idea consiste en realizar dos pistas paralelas con luces led, estas simularán el movimiento de los vehículos. Y mediante una aplicación, la cual deberán descargar dos jugadores para que cada uno se comunique con una de las dos placas Arduino UNO. Uno de los jugadores será el “host”, el cual podrá establecer una cantidad de vueltas a correr y cuando ambos jugadores estén listos, la carrera comenzará. Para hacer que los vehículos se muevan, los jugadores deberán tocar en sus celulares lo más rápido posible el botón de avanzar.

## Materiles utilizados

* Dos arduinos UNO
* Dos módulos bluetooth para arduino
* Una tira de 3600 leds programables Neopixel
* Cables
* Una placa de pruebas para conectar los componentes
* Dos celulares
* Un contenedor plástico para cubrir los componentes electrónicos

## Aplicaciones utilizadas para el desarrollo

* Autodesk Tinkercad para la simulación de las conecciones
* Aplicación de arduino para cargar el código en las placas
* MIT App-Inventor para el desarrollo de la aplicación de android

## Costos en USDs

* Arduino UNO — $27,00 x2
* Módulo bluetooth — $13,00 x2
* Tira de leds — $81,37 x1
* Resistencias — $2,00 x1 
* Condensador — $3,80 x2

## Primer prototipo

En esta imagen se ve el diseño realizado en tinkercad. En la aplicación no hay módulos bluetooth o módulos wifi, por lo cual no sería posible mandar a las placas la señal de que avancen los vehículos, entonces, a fines de simulación, colocamos dos botones para que avancen los vehículos.

## Diseño de la aplicación

Diseño del menú de la aplicación, Menú de selección de usuario y Menú de jugador Host. El menú de invitado es idéntico al de host, solamente que no se cuenta con la opción de configurar las vueltas a realizar.



