# Cerradura RFID

### Universidad Blas Pascal - Ing. Tele. - TD2 - 2022
------------------------------------------------------------------------------------------

## Introducción

El objetivo de este proyecto es lograr un sistema de cerradura automatizado con control de acceso utilizando un RFID que sera conectada a unas de las entradas de los laboratorios para asi lograr un contro de acceso, dandole una tarjeta de acceso a los profesores que soliciten entrar, y con ellas tener un registro 
utilizaremos un ESP-32 conectado a un RFID con un relay a la cerradura conectado con un panel LCD que nos dira si el acceso es permitido o denegado que este se cargara a una base de datos que en esta se observara quienes accedieron al laboratorio, la idea principalmente era poder adquirir los datos de movimientos en el laboratio y poder controlar todo via internet 

## NodeMCU ESP-32S

El NodeMCU ESP-32S es una de las placas de desarrollo creadas por NodeMcu para evaluar el módulo ESP-WROOM-32. Se basa en el microcontrolador ESP32 que cuenta con Wifi, Bluetooth, Ethernet y soporte de baja potencia, todo en un solo chip.

## Estableciendo la conexión entre el servidor MQTT y ESP32 

IoT es un sistema que conecta los dispositivos a los que se puede acceder a través de Internet. Hay varias plataformas y protocolos en la nube, MQTT es uno de los protocolos más utilizados para proyectos de IoT. ESP32 es el sucesor del módulo ESP8266 WiFi , con muchas características avanzadas como es una CPU de doble núcleo de 32 bits con WiFi incorporado y Bluetooth de modo dual con una cantidad suficiente de 30 pines de E/S. Si bien MQTT significa Transporte de telemetría de Message Queue Server, es un sistema donde podemos publicar y suscribir mensajes como cliente. Al usar MQTT puede enviar comandos para controlar salidas, leer y publicar datos de sensores y mucho más.

## UBIDOTS

es el servicio que utilizamos como servidor MQTT para enviar nuestros datos para tener registro de entrada
al cual ingresaremos con la cuenta "user: TecnicasDigitales2, contraseña;Tecnicasdigitales2"
alli nos dirigiremos a dispositivos y alli encontraremos el registro de nuestra RFID y dirigiendonos a asistencia tendremos un registro de quienes han ingresado al laboratorio con fecha y horario. 
el mail que estaremos utilizando en la cuenta de ubidots es ts2.ubp@gmail.com , contraseña: Tecnicasdigitales2 





------------------------------------------------------------------------------------------
### Por: Romano Facundo; Arndt Haase Eric Julian ; Crerar Juan Jose 
