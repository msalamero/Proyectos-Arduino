#                                                                           SUMO LUCHA

## Integrantes:

* Octavio Douglas
* Ignacio Galvan
* Tomas Calzada
* Fabricio Marques
* Bautista Menzi

## Intrdución.

En este informe se va a mencionar nuestro proyecto de Arduino para la materia de LAB 1.
Nuestro proyecto consiste en un robot sumo, el cual va a tener dos modos de funcionamiento dependiendo de lo que quiera el usuario; el primero es el modo manual el cual tendrá cinco botones, el de arriba es para que avance para adelante, el del medio para que se pare completamente, el de abajo para que retroceda, y el de los costados para que gire del lado que se elija respectivamente. El segundo modo es el automático en el cual funcionará por sí solo y este tiene un funcionamiento único ya que va a estar constantemente girando a una velocidad mínima hasta que encuentre un objeto el cual será detectado mediante un sensor ultrasónico e ira hacia adelante hasta que no encuentre más un objeto el sensor comentado anteriormente.
![WhatsApp Image 2022-11-28 at 17 00 02](https://user-images.githubusercontent.com/119351227/204409799-41e527f9-01fa-4d1b-adee-97fae6a31d5b.jpeg) 
![WhatsApp Image 2022-11-28 at 16 58 01](https://user-images.githubusercontent.com/119351227/204409823-1c78876f-a915-47b9-aef9-47b3aa15b936.jpeg)

## FUENTE DE INSPIRACIÓN.

La idea surgió entre dos grupos del mismo curso sobre hacer unos robots “sumo” y que peleen entre ellos. Después de esto, nos pusimos a ver videos en YouTube como https://youtu.be/L-IO7iLJEJQ y https://youtu.be/O6_1q7rJWSY para poder guiarnos y ver algunos ejemplos.

## PROPUESTA MEJORADA.

Gracias a los videos y mediante una lluvia de ideas pudimos decretar nuestra propuesta para este trabajo final. Básicamente, como veníamos comentando, vamos a hacer un robot “sumo”, el cual va a estar equipado por distintos dispositivos para poder realizar su función, la cual es sacar del ring a su contrincante.
Por ejemplo, para moverse y reaccionar a los movimientos del rival tendrá dos motores y un sensor ultrasónico. El mismo va a tener una batería de 9V, la cual tendrá un conjunto de Leds que dirán cuál es su nivel de batería. Además, contará con un dispositivo Bluetooth para que se pueda controlar mediante App Inventor.

## COMPONENTES.

https://user-images.githubusercontent.com/119351227/204410368-1d71bb8d-8185-4baa-b6c3-db5e3fdd43d2.mp4

### Nuestro “sumo” tiene integrados varios componentes Arduino. Como, por ejemplo: 

*	Dos motores con un L9110 que los controla
*	Un Arduino UNO 
*	Un sensor ultrasónico
*	Un dispositivo Bluetooth
*	Una placa de prueba

### Además de los componentes nombrados, utilizará otros como:

*	Tres ruedas (dos para que pueda moverse y una direccional)
*	Luces Led
*	Una carcaza
*	Una batería 9V
*	Cables Hembra y Macho para las conexiones.

## DIFICULTADES DURANTE EL PROCESO.

Las principales dificultades que tuvimos fueron con el Arduino MEGA y el LCD 16.
Arduino MEGA: Tuvimos que cambiarlo a un Arduino UNO ya que nos salía error al ingresar una nueva programación.
LCD 16: Lo cambiamos por un led rojo, amarillo y verde, ya que nuestro LCD no imprimía lo que queríamos.

![image](https://user-images.githubusercontent.com/119351227/204411089-6f4fa6f6-2f99-44b2-80ee-22128772e410.png) ![image](https://user-images.githubusercontent.com/119351227/204411112-d9f9e7a0-f333-4c38-a95b-c8e733e4f1a5.png)

## MODELO TINKERCAD.

https://www.tinkercad.com/things/dUs0up8uQ2K-brilliant-curcan-blad/edit?sharecode=PA3jD7DBp71zE36tLr9bMUMX-hMJEe8Dt2OTYhEdPaQ

![image](https://user-images.githubusercontent.com/119351227/204410666-39820415-6c19-470b-933d-29947e50d406.png)  ![image](https://user-images.githubusercontent.com/119351227/204410709-fc832613-ec09-45d7-81be-d2117f48e4fb.png) ![image](https://user-images.githubusercontent.com/119351227/204410784-fb76ac78-a36e-41b2-99fd-1f40df8f7f44.png)

## PROCESO DEL SUMO.

![image](https://user-images.githubusercontent.com/119351227/204410849-dc5c89d6-f3c8-4e3e-8739-59f65de33bb1.png) ![image](https://user-images.githubusercontent.com/119351227/204410854-679ff9f2-5f4b-45d8-b3fa-8d95717df194.png)

## APP INVENTOR DISEÑO.

![image](https://user-images.githubusercontent.com/119351227/204411294-e48561d8-e8ef-4a64-9e50-80e72e354fc7.png)

 ## APP INVENTOR: BLOQUES.

![image](https://user-images.githubusercontent.com/119351227/204411399-7e471042-88d8-4d3c-ad8b-021466125eb9.png) ![image](https://user-images.githubusercontent.com/119351227/204411411-61ae5431-991d-4eed-b0c7-258ac9240450.png)

## PROYECTO TERMINADO.

![image](https://user-images.githubusercontent.com/119351227/204411466-5108718c-1421-4fd4-b5c8-a9ab298afcaa.png) ![image](https://user-images.githubusercontent.com/119351227/204411480-f10f80a1-f83d-4d13-a82a-ab5ed669b2ee.png) ![image](https://user-images.githubusercontent.com/119351227/204411505-49afdef3-b346-47b0-af69-4edb875f57b0.png)



