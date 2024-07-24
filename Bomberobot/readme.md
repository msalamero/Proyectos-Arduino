“BombeBot”


Alumnos:  Milagros Mercado, Tomas Caceres y Guadalupe Mediavilla.
Profesores: Salamero Martin y Nano Monica.
Materia: Laboratorio 1.
Fecha de Entrega: 24/07/2024.

















Índice
1.	Introducción
2.	Arquitectura del Proyecto
3.	Instalación y Configuración
1.	Requisitos Previos
2.	Pasos de Instalación
4.	Descripción de Archivos y Directorios
1.	app.json
2.	JoystickScreen.tsx
3.	HomeScreen.tsx
4.	main.cpp (Arduino)
5.	Detalles de Implementación
1.	Gestión de Dispositivos Bluetooth
2.	Manejo del Joystick
3.	Control del Servo
4.	Control de la Bomba de Agua
5.	Ping-Pong para Verificar Conexión
6.	Generación del APK
7.	Instrucciones de uso
8.	Componentes Utilizados
9.	Diseño 3D y Conexiones
10.	Conclusión




El proyecto BombeBot es una aplicación móvil diseñada para controlar remotamente un vehículo de bomberos utilizando Bluetooth. La aplicación permite manejar las ruedas, el servo y la bomba de agua del vehículo desde un dispositivo móvil. Esta documentación proporciona una descripción detallada del proyecto, incluyendo su instalación, configuración y uso.
Arquitectura del Proyecto
El proyecto está compuesto por dos partes principales:
•	Aplicación móvil: Desarrollada utilizando React Native y Expo, esta aplicación permite la comunicación Bluetooth con el vehículo de bomberos.
•	Firmware del vehículo: Desarrollado en un lenguaje para Arduino, controla los motores, el servo y la bomba de agua del vehículo.




Instalación y Configuración
Requisitos Previos
•	Node.js y npm instalados en el sistema.
•	Expo CLI instalado globalmente
npm install -g expo-cli
•	Plataforma Arduino IDE para cargar el firmware en el microcontrolador.
Pasos de Instalación
1.	Descomprimimos el archivo descargado: Descomprimimos el archivo descargado en el directorio.
2.	Instalar dependencias: Abrimos una terminal y navegamos al directorio de la aplicación descomprimida. Luego, instalamos las dependencias necesarias.
npm install
3.	Configurar Expo: Modificamos app.json para ajustar la configuración del proyecto según nuestras necesidades.
4.	Iniciar la aplicación:
npx expo start
5.	Cargar el firmware en Arduino:
o	Abrimos main.cpp en Arduino IDE
o	Conecta el microcontrolador y cargamos el programa.
Modificamos el jumper antes de compilar utilizando Arduino IDE:
•	Cambiamos el jumper que se encuentra en la parte superior del camión a la posición abierto (pin 1 y 2), lo cual desactiva el módulo Bluetooth y permite compilar.
•	Después de compilar, volver a la posición cerrado (pin 2 y 3) para activar la alimentación del Bluetooth.




4. Descripción de Archivos y Directorios
app.json

Este archivo contiene la configuración del proyecto Expo.

Json

{
"expo": {
"name": "BombeBot",
"slug": "BombeBot",
"version": "1.0.0",
"orientation": "landscape",
"icon": "./assets/icon.png",
"userInterfaceStyle": "light",
"splash": {
"image": "./assets/splash.png",
"resizeMode": "contain",
"backgroundColor": "#ffffff"
},
"updates": {
"fallbackToCacheTimeout": 0
},
"assetBundlePatterns": [
"*/"
],
"ios": {
"supportsTablet": true,
"bundleIdentifier": "com.bombebot.ubp"
},
"android": {
"adaptiveIcon": {
"foregroundImage": "./assets/adaptive-icon.png",
"backgroundColor": "#FFFFFF"
},
"permissions": [
"android.permission.BLUETOOTH_ADVERTISE",
"android.permission.BLUETOOTH_CONNECT",
"android.permission.BLUETOOTH_SCAN",
"android.permission.ACCESS_FINE_LOCATION",
"android.permission.ACCESS_COARSE_LOCATION"
],
"package": "com.bombebot.ubp"
},
"web": {
"favicon": "./assets/favicon.png"
},
"plugins": [
"./withBluetoothClassic"
]
}
}

JoystickScreen.tsx
Este archivo contiene la pantalla principal de la aplicación, donde se maneja el control del joystick, el servo y la bomba de agua.

HomeScreen.tsx
Este archivo contiene la pantalla inicial de la aplicación, donde se listan y gestionan los dispositivos Bluetooth.

main.cpp (Arduino)
Este archivo contiene el firmware para el microcontrolador Arduino, encargado de controlar los motores, el servo y la bomba de agua del vehículo.
5.	#include <Arduino.h>
6.	#include <AFMotor.h>
7.	#include <Servo.h>
8.	
9.	AF_DCMotor motor1(1);
10.	AF_DCMotor motor2(2);
11.	AF_DCMotor motor4(4);
12.	Servo myServo;
13.	
14.	String command = "";
15.	unsigned long lastPingTime = 0;
16.	void resetBluetooth();
17.	void handleCommand(String cmd);
18.	void processSingleCommand(String cmd);
19.	void processCombinedCommand(String cmd);
20.	
21.	void setup() {
22.	
23.	Serial.begin(9600);
24.	myServo.attach(10);
25.	motor1.setSpeed(255);
26.	motor2.setSpeed(255);
27.	motor4.setSpeed(255);
28.	
29.	lastPingTime = millis();
30.	}
31.	
32.	void loop() {
33.	while (Serial.available()) {
34.	char c = (char)Serial.read();
35.	if (c == '\n') {
36.	handleCommand(command);
37.	command = "";
38.	} else {
39.	command += c;
40.	}
41.	}
42.	if (millis() - lastPingTime > 15000) {
43.	resetBluetooth();
44.	}
45.	}
46.	
47.	void handleCommand(String cmd) {
48.	lastPingTime = millis();
49.	
50.	if (cmd.startsWith("PING")) {
51.	Serial.println("PONG");
52.	} else if (cmd.indexOf('-') != -1) {
53.	processCombinedCommand(cmd);
54.	} else {
55.	processSingleCommand(cmd);
56.	}
57.	
58.	void processSingleCommand(String cmd) {
59.	if (cmd.startsWith("FWD")) {
60.	int speed = cmd.substring(3).toInt();
61.	motor1.setSpeed(speed);
62.	motor2.setSpeed(speed);
63.	motor1.run(FORWARD);
64.	motor2.run(FORWARD);
65.	} else if (cmd.startsWith("BCK")) {
66.	int speed = cmd.substring(3).toInt();
67.	motor1.setSpeed(speed);
68.	motor2.setSpeed(speed);
69.	motor1.run(BACKWARD);
70.	motor2.run(BACKWARD);
71.	} else if (cmd.startsWith("LFT")) { /
72.	int speed = cmd.substring(3).toInt();
73.	motor1.setSpeed(speed);
74.	motor2.setSpeed(speed);
75.	motor1.run(FORWARD);
76.	motor2.run(BACKWARD);
77.	} else if (cmd.startsWith("RGT")) {
78.	int speed = cmd.substring(3).toInt();
79.	motor1.setSpeed(speed);
80.	motor2.setSpeed(speed);
81.	motor1.run(BACKWARD);
82.	motor2.run(FORWARD);
83.	} else if (cmd == "STP") {
84.	motor1.run(RELEASE);
85.	motor2.run(RELEASE);
86.	} else if (cmd == "BMP") {
87.	motor4.run(FORWARD);
88.	} else if (cmd == "STB") {
89.	motor4.run(RELEASE);
90.	} else if (cmd.startsWith("SRV")) {
91.	int angle = cmd.substring(3).toInt();
92.	myServo.write(angle);
93.	} else {
94.	
95.	}
96.	}
97.	
98.	void processCombinedCommand(String cmd) {
99.	int separatorIndex = cmd.indexOf('-');
100.	String firstPart = cmd.substring(0, separatorIndex);
101.	String secondPart = cmd.substring(separatorIndex + 1);
102.	
103.	processSingleCommand(firstPart);
104.	processSingleCommand(secondPart);
105.	}
106.	
107.	void resetBluetooth() {
108.	motor1.run(RELEASE);
109.	motor2.run(RELEASE);
110.	motor4.run(RELEASE);
111.	myServo.write(90);
112.	Serial.println("Desconectando por inactividad...");
113.	}
114.	


5. Detalles de Implementación
Gestión de Dispositivos Bluetooth
La gestión de dispositivos Bluetooth se realiza principalmente en HomeScreen.tsx. Aquí se escanean los dispositivos, se conectan y se desconectan. Además, se almacenan en AsyncStorage para mantener la persistencia de la conexión.

javascript
const startScan = async () => {
setScanning(true);
setDevices([]);

try {
const bondedDevices = await RNBluetoothClassic.getBondedDevices();
const foundDevices = await RNBluetoothClassic.startDiscovery();

const storedDevice = await AsyncStorage.getItem('selectedDevice');
if (storedDevice) {
const parsedDevice = JSON.parse(storedDevice);
const allDevices = [...new Set([...bondedDevices, ...foundDevices, parsedDevice])];
const filteredDevices = allDevices.filter((device, index, self) =>
index === self.findIndex((d) => d.address === device.address) && device.name && device.name.includes('HC-05')
);
setDevices(filteredDevices);
} else {
const allDevices = [...new Set([...bondedDevices, ...foundDevices])];
const filteredDevices = allDevices.filter((device, index, self) =>
index === self.findIndex((d) => d.address === device.address) && device.name && device.name.includes('HC-05')
);
setDevices(filteredDevices);
}
} catch (error) {
console.error('Error al escanear dispositivos', error);
}

setScanning(false);
};

Manejo del Joystick
El control del joystick se maneja en JoystickScreen.tsx usando el componente AxisPad para capturar los eventos de movimiento y enviar comandos al vehículo.

javascript
const handlePadEvent = (event: AxisPadTouchEvent) => {
const { eventType, ratio } = event;
const intSpeedX = Math.floor(Math.min(255, Math.max(0, Math.abs(ratio.x) * 255)));
const intSpeedY = Math.floor(Math.min(255, Math.max(0, Math.abs(ratio.y) * 255)));

if (eventType === 'start') {
console.log('Inicio x', ratio.x, 'Inicio y', ratio.y);
} else if (eventType === 'end') {
console.log('Fin x', ratio.x, 'Fin y', ratio.y);
sendCommand('STP');
} else if (eventType === 'pan') {
console.log('Pan x', ratio.x, 'Pan y', ratio.y);
if (ratio.y < -0.2) {
sendCommand(FWD${intSpeedY});
} else if (ratio.y > 0.2) {
sendCommand(BCK${intSpeedY});
}

if (ratio.x < -0.2) {
sendCommand(RGT${intSpeedX});
} else if (ratio.x > 0.2) {
sendCommand(LFT${intSpeedX});
}
}
};
Control del Servo
El control del servo se realiza a través de un Slider que permite ajustar el ángulo del servo. Los cambios se envían al vehículo como comandos SRV.

javascript
const handleServoChange = async (value) => {
setServoAngle(value);
await sendCommand(SRV${value});
};

Control de la Bomba de Agua
La bomba de agua se controla mediante un botón de tipo push. Al mantener presionado el botón, se envía repetidamente el comando para encender la bomba, y al soltarlo, se envía el comando para apagarla.

javascript
const startBomba = async () => {
bombaIntervalRef.current = setInterval(async () => {
await sendCommand('BMP');
}, 100);
setBombaOn(true);
};

const stopBomba = async () => {
clearInterval(bombaIntervalRef.current);
await sendCommand('STB');
setBombaOn(false);
};

const handleBombaPressIn = () => {
startBomba();
};

const handleBombaPressOut = () => {
stopBomba();
};

Ping-Pong para Verificar Conexión
Para verificar la conexión continua entre la aplicación y el vehículo, se implementa un sistema de ping-pong. Si no se recibe una respuesta en 15 segundos, se asume que la conexión se ha perdido y se resetea el módulo



Conexiones de Arduino
En esta sección se detallan las conexiones físicas necesarias para que el sistema funcione correctamente. Es fundamental seguir estos esquemas para garantizar el correcto funcionamiento de los componentes.
Conexiones del Hardware
1.	Motores DC:
o	Motor 1: Conectado a los pines M1 y M2 del controlador de motores (AFMotor).
o	Motor 2: Conectado a los pines M3 y M4 del controlador de motores (AFMotor).
2.	Servo:
o	Pin de Control: Conectado al pin 10 del Arduino.
3.	Bomba de Agua:
o	Motor de la Bomba: Conectado al pin M5 del controlador de motores (AFMotor).
4.	Módulo Bluetooth:
o	RX: Conectado al pin TX del Arduino.
o	TX: Conectado al pin RX del Arduino.
o	VCC: Alimentación de 5V.
o	GND: Tierra.


Conclusión
El proyecto BombeBot ha demostrado ser una solución efectiva para controlar un vehículo de bomberos mediante una interfaz móvil, utilizando tecnología Bluetooth para la comunicación entre la aplicación y el hardware del vehículo. La integración de componentes de hardware y software ha permitido desarrollar un sistema funcional que realiza las siguientes tareas:
1.	Control Remoto del Vehículo: La aplicación móvil desarrollada en React Native y Expo permite controlar el movimiento del vehículo, así como la dirección y la activación de la bomba de agua. La interfaz intuitiva asegura que los usuarios puedan manejar el vehículo con facilidad.
2.	Comunicación Eficiente: El módulo Bluetooth HC-05 ha facilitado una comunicación confiable entre la aplicación y el microcontrolador Arduino. La implementación de un sistema de ping-pong asegura la continuidad de la conexión y la gestión adecuada de posibles desconexiones.
3.	Manejo de Componentes Hardware: El uso del controlador de motores AFMotor ha simplificado el control de los motores DC, mientras que la biblioteca Servo ha permitido un control preciso del servomotor para ajustar la dirección del vehículo. La bomba de agua, controlada por el firmware en Arduino, simula el sistema de rociado del vehículo de bomberos.
4.	Facilidad de Configuración e Instalación: Las instrucciones detalladas para la instalación y configuración tanto del software como del firmware aseguran que el proyecto sea accesible para futuros desarrolladores. La configuración del entorno de desarrollo, así como las conexiones de hardware, están claramente especificadas para evitar errores comunes.
5.	Experiencia del Usuario: La aplicación ofrece una experiencia de usuario satisfactoria mediante un diseño sencillo y funcionalidades bien implementadas. El uso del joystick para el control direccional y la interfaz de botones para la bomba de agua proporcionan una interacción clara y eficiente con el vehículo.
En resumen, el proyecto BombeBot ha logrado integrar con éxito las tecnologías necesarias para crear un sistema de control remoto eficaz y fácil de usar. Los desafíos enfrentados durante el desarrollo han sido superados mediante una cuidadosa planificación y la implementación de soluciones técnicas adecuadas. Este proyecto sirve como un excelente ejemplo de cómo combinar el desarrollo de software con el hardware para crear aplicaciones innovadoras y funcionales.


6. Generación del APK
Para generar el APK de la aplicación BombeBot, se siguen estos pasos:
Prebuild de Expo:

npx expo prebuild

Compilar la aplicación Android: Navega al directorio android y ejecuta el siguiente comando:

cd android
./gradlew assembleRelease

Encontrar el APK generado: El APK se generará en el directorio android/app/build/outputs/apk/release/.

Instrucciones de Uso
Encender el vehículo de bomberos y asegúrarse de que el módulo Bluetooth esté activado.
Abrir la aplicación BombeBot en eldispositivo móvil.
La aplicación escaneará automáticamente los dispositivos Bluetooth disponibles. Seleccionar el dispositivo con el nombre HC-05.
Utilizar el joystick para controlar las ruedas del vehículo, el slider para ajustar el ángulo del servo, y el botón para controlar la bomba de agua.


