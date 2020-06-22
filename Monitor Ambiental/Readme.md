# Monitor Ambiental
## By Franco Geremia y Facundo Facello.
### Universidad Blas Pascal - Ing. Informática - Lab 1 - 2019
------------------------------------------------------------------------------------------
## Idea original: 

Crear un robot equipado con todos los sensores disponibles, que cuente con un sistema de movilidad y que sea controlable desde un dispositivo con Bluetooth.
Usos: Investigación, rescates (situaciones de peligro) o recreativos.
Luego de trabajar en el proyecto, al cual decidimos llamar August, durante estos meses, se pueden tener en cuenta la siguiente situación, avances y cambios:

PROYECTO: AUGUST

## Se implementaron los siguientes componentes:

- Piezo buzzer (12V)
- Modulo Bluetooth (HC-05)
- Modulo LED (KY-009)
- Sensor de temperatura y humedad (KY-015)
- Sensor de distancia ultrasónico (HC-SR04)
- Sensor de luz (GL55)
- Sensor de luz infrarroja (KY-026)
- Sensor de gas (MQ-2, MQ-5 y MQ-7)

Los resultados fueron los siguientes:

## ACTUALIDAD: 

Decidimos centrarnos en la parte esencial del proyecto, la cual es el uso de los sensores y módulos, una vez terminada vamos a proceder con el sistema de movilidad y el diseño del robot (en sentido de estructura externa).

## FUNCIONAMIENTO: 

El robot debe conectarse a una fuente de energía (cargador portátil por ejemplo) para funcionar, luego se debe establecer una conexión a través de cualquier aplicación que maneje Bluetooth y permita enviar comandos a August, una vez conectado aparecerá en el dispositivo un menú que contiene todas las funciones del robot:
1. Sensor de Distancia
2. Sensor de Monóxido de Carbono
3. Sensor de Gas Natural 
4. Sensor de Humo 
5. Sensor de Luz
6. Sensor de Fuego
7. Reproducir Música
8. Apagar LED

Cada vez que se selecciona una de las opciones se pueden observar en el dispositivo lo que esta haciendo o detectando el robot y un color que indica lo que significa esa información, este color se presenta en el LED incorporado en el mismo.
Algunos de los sensores se encuentran configurados para reaccionar a diferentes valores de lo que detectan para evitar detecciones erróneas, otros componentes como el buzzer y los futuros motores funcionan independientemente de los sensores ya que no afectan a su desarrollo. 
 
### TEMPERATURA Y HUMEDAD: 
Debido a un error en el funcionamiento del único modulo disponible este tuvo que ser descartado del modelo original para evitar que proporcionara datos erróneos.

### PLACA ARDUINO: 
Comenzamos con una placa Arduino Leonardo pero esta tuvo que ser cambiada por un placa Arduino Mega 2560 para permitir el funcionamiento correcto de todos los componentes, incluyendo a los motores,  y para que se establezca un comunicación adecuada entre el módulo Bluetooth y el dispositivo desde donde se controle.

### MOTORES: 
Estos no fueron implementados todavía ya que no había disponibilidad de los necesarios, actualmente estamos buscando una alternativa para conseguir dichos motores, ya sea la compra de nuevos o el uso de otros que funcionen adecuadamente conforme al proyecto.

Seguimos desarrollando este proyecto y buscamos alcanzar la meta propuesta en un principio sin importar los contratiempos.
