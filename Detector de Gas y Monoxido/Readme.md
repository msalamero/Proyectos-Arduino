# Detector de Gas y Monóxido de Carbono
## By Blanco, LEANDRO  /  Zeitune, PABLO MARTIN   

## Descripción

Se realizó un detector autónomo de gas y monóxido de carbono con dos entradas analógicas y una salida digital, el cual se conecta a internet mediante una conexión WiFi, permitiendo ser monitoreado y accionado mediante una aplicación HTML o dispositivo móvil donde permite recibir notificaciones a través de la suscripción del Tópico “gases”, la detección de los gases y accionar la salida de forma automática (Buzzer). El dispositivo cuenta con dos sensores electroquímicos de gases, estos son leídos por un microcontrolador y enviados a través de una conexión WiFi que se encarga de conectarse con un servidor en la nube mediante el protocolo MQTT. Se obtuvo un dispositivo robusto capaz de detectar pérdidas de GAS y detectar CO de forma rápida y sin falsas.
Como parte del trabajo conjunto del aula se obtuvo un enlace rápido y eficiente a través de internet al utilizar un protocolo utilizado en dispositivos IOT. 

Palabras Clave: Aplicación móvil, Detector de gas, Detector de monóxido de carbono, IOT, MQTT, WiFi.

### NodeMCU ESP-32S

El NodeMCU ESP-32S es una de las placas de desarrollo creadas por NodeMcu para evaluar el módulo ESP-WROOM-32. Se basa en el microcontrolador ESP32 que cuenta con Wifi, Bluetooth, Ethernet y soporte de baja potencia, todo en un solo chip.

### Estableciendo la conexión entre el servidor MQTT y ESP32 

IoT es un sistema que conecta los dispositivos a los que se puede acceder a través de Internet. Hay varias plataformas y protocolos en la nube, MQTT es uno de los protocolos más utilizados para proyectos de IoT.
ESP32 es el sucesor del módulo ESP8266 WiFi , con muchas características avanzadas como es una CPU de doble núcleo de 32 bits con WiFi incorporado y Bluetooth de modo dual con una cantidad suficiente de 30 pines de E/S.
Si bien MQTT significa Transporte de telemetría de Message Queue Server, es un sistema donde podemos publicar y suscribir mensajes como cliente. Al usar MQTT puede enviar comandos para controlar salidas, leer y publicar datos de sensores y mucho más. Hay dos términos principales en MQTT, Cliente y Broker.
 
#### ¿Qué es MQTT Client & Broker? 
Cliente MQTT:  un cliente MQTT ejecuta una biblioteca MQTT y se conecta a un agente MQTT a través de una red.  Tanto el editor como el suscriptor son clientes MQTT. El editor y el suscriptor se refieren a si el cliente está publicando mensajes o suscribiéndose a mensajes.
Intermediario MQTT:  el intermediario recibe todos los mensajes, filtra los mensajes, determina quién está suscrito a cada mensaje y envía el mensaje a estos clientes suscritos.

#### Explicación del Código ESP32-MQTT Broker:
El código completo para  conectar ESP32 con el agente MQTT se proporciona al final . Aquí, estamos usando  Arduino IDE para programar ESP32 . Primero,  instalamos la biblioteca WiFi.h y la biblioteca PubSubClient.h .

La biblioteca PubSubClient nos permite publicar / suscribir mensajes en tópicos.

![1](files/1.png)

Ahora declaramos algunas variables globales para nuestras conexiones WiFi y MQTT.
![2](files/2.png)

La función setup_wifi  verificará el WiFi, ya sea que esté conectado a la red o no, también proporcionará la dirección IP e imprimirá en el monitor serie.
![3](files/3.png)

A continuación, mientras funciona en bucle, se conectará al servidor MQTT y lo imprimirá en el monitor en serie. Este proceso se ejecutará en un bucle hasta que se conecte.

![4](files/4.png)

Ahora especificaremos una función de devolución de llamada y en esta función, primero imprimiremos el nombre del tema y luego recibiremos el mensaje.

![5](files/5.png)

Conectando con la red WiFi y servidor MQTT:

![6](files/6.png)

### Sensores de gas MQ


![7](files/7.jpg)

Los sensores de gas de la serie MQ son sensores analógicos por lo que son fáciles de implementar con cualquier microcontrolador.

