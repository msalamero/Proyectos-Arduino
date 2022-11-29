# Cerradura Electronica - Grupo 6


## Introduccion

El objetivo de nuestro trabajo final es desarrollar una cerradura electronica, para mejorar la seguridad y agilidad de el ingreso a un hogar o a un espacio de trabajo. Se detallan a continuacion todos los procesos que realizamos para concluir con nuestro trabajo final.

## Antecedentes

En cuanto a los antecedentes, lo que nos motivo a realizar este proyecto de cerradura electronica con los integrantes del grupo, fue una conversacion que tuvimos con nuestra profesora, donde nos encontrabamos en la puerta del laboratorio a la espera del ingreso, pudimos observar que la llave no era la correcta y ademas se complicaba el acceso de los alumnos a horario. Otra cosa que nos inspiro a realizar el proyecto, fue pensar en los profesores, que luego de una larga jornada de clases tienen que ir hasta bedelia ya sea para buscar o para dejar una llave.

## Propuesta

Nuestra propuesta como grupo es trabajar con una cerradura de tipo cerrojo que va a ser accionada mediante un servo, la cual colocariamos en una puerta del laboratorio por ejemplo, como se nos habia ocurrido en nuestros antecedentes. Para manipular esta cerradura, tenemos 3 tipos distintos de acceso:
> Uso de RFID
> 
> Uso de Teclado
> 
> Uso de aplicacion


![WhatsApp Image 2022-11-29 at 00 09 50](https://user-images.githubusercontent.com/89396243/204429450-07047a34-cd48-4252-ac2b-aa3e2de346ac.jpeg)


Donde para el RFID poseemos una tarjeta de acceso la cual esta cargada en el codigo del arduino y es la que nos permite ya sea apertura o cierre de la cerradura y ademas el cambio de la contraseña. Con el teclado de tipo 4x4, podemos tambien ya sea indicar el armado o el desarmado de la cerradura a traves de una contraseña precargada en el codigo del IDE Arduino que puede ser cambiada si entramos en el modo de cambiar contraseña. Por ultimo, el ultimo metodo de acceso, es una aplicacion desarrollada en la plataroforma de [App Inventor](http://appinventor.mit.edu/). En esta aplicacion, se utiliza la base de datos TinyBD, con la cual podemos realizar la gestion de los usuarios y contraseñas segun nuestras preferencias.

## Componentes a utilizar, con valores en pesos argentinos y en dolares.

> Arduino UNO: $4000 - u$s: 13,79.
> 
> Lector RFID: $ 1000 - u$s: 3,44.
>
> Servo: $ 900 – u$s: 3,10.
>
>Placa de pruebas: $ 875 - u$s: 3,01.
> 
> Pantalla LED 16x2 I2C: $ 2300 - u$s: 7,93.
> 
> Teclado numérico: $ 700 – u$s: 2,41.
>
> Buzzer: $ 450 – u$s: 1,55.
>
> Led: $ 12 cada uno – u$s: 0,08.
>
> Resistencias: $ 290 - u$s: 1.

# TOTAL: $10543 - u$s: 36,34

## Diseño en TinkerCad

A continuacion, se adjunta una foto sobre el diseño realizado en [TINKERCAD](https://www.tinkercad.com/). Esta es la pagina oficial.

![image](https://user-images.githubusercontent.com/89396243/204426067-e0f36551-2e06-4ec5-a46a-fed7281508ff.png)

La imagen se encuentra editada, ya que el modulo de RFID no se encuentra disponible en el apartado de diseño de circuitos electronicos. Se adjunta aqui, el link del diseño del circuito electronico mas aproximado, realizado en tinkercad. Presione [aqui](https://www.tinkercad.com/things/1cVKXzhgRyp-lab-final/editel?sharecode=W6T_4yGCV-lJYgSF247wd49hwc-bkN7tiAkDdNMAGq8) para visualizarlo.

## Dificultades

Como dificultades, nos surgio que fue dificil implementar la cerradura de tipo cerrojo, ya que a la hora de imprimir un archivo 3d de esta cerradura que encontramos en internet, el archivo se encontraba roto o mal grabado, por lo cual tuvimos que realizar nuestro propio diseño de la misma en la pagina de Tinkercad, importando el archivo con la extension .STL. Otra dificultad que nos surgio fue para leer los codigos de 4 bytes de cada una de las tarjetas a utilizar, ya quue tuvimos que desarrollar otro programa que se encargue de realizar esto. A continuacion, la otra dificultad que surgio fue sobre la conexion Bluetooth de la app con el arduino, ya que luego de leer mucha informacion vimos que debiamos realizar la conexion en los pines 0 y 1 del arduino, pero luego de tantas pruebas, vimos que estos pines no nos funcionaron para ello, por lo que tuvimos que conectarlo en los pines 9 y 10. Siguiente a esto, la dificultad que tuvimos fue no nos alcanzaban la cantidad de pines del arduino para todas las componentes que teniamos que utilizar, para esto tuvimos que declarar los pines analogicos A, como salidas para poder utilizarlos como salida para los modulos utilizados. Por ultimo otra dificultad que tuvimos fue el movimiento del servo, ya que debimos implementar un alambre especial para realizar el movimiento del pestillo y debimos calcular los angulos de movimiento para su correcto funcionamiento.

## Conclusion

Como conclusion, podemos decir que es incalculable el potencial que puede lograr una placa de Arduino, lo cual vemos de total importancia estudiar y comprender tanto su funcionamiento como el de todas sus componentes, ya que podriamos realizar diversos proyectos utiles para nuestra vida cotidiana.

Como el funcionamiento de la cerradura, podemos ver que su precio es considerablemente mas barato que el resto de las cerraduras electronicas que se encuentran en el mercado actual y podemos observar tambien, que es una increible oportunidad para implementarla tanto en los laborartorios de nuestra facultad, como tambien en cada uno de nuestros hogares.

# Integrantes

> Federico Casani
>  
>  Alessandro Chavarino
>  
>  Francisco Agustin Muñoz

# Profesores

> Monica Liliana Nano
> 
> Martin Salamero

# Universidad

![image](https://user-images.githubusercontent.com/89396243/204428114-5f1dea2a-5d82-46ee-ac6d-f158c1727183.png)
