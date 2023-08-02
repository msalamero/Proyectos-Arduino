#PROYECTO FINAL - LABORATORIO I
##PIANO/TECLADO MIDI
###Integrantes: David Ignacio Abril Perrig, Facundo Nehuén Gomez Geneiro, Lisandro Javier Perez
Docentes: Lic. Mónica Liliana Nano, Ing. Martín Alejandro Salamero
Objetivo: Propuesta formal del trabajo final

RESUMEN
En este informe se propone y desarrolla la idea de un proyecto final en el ámbito de la
electrónica básica para la materia “Laboratorio I” de la Universidad Blas Pascal.
Se expone la idea para una mejora de cualquier Teclado/Piano eléctrico que no tenga la
posibilidad de conectarse mediante la tecnología MIDI.
Un teclado/piano eléctrico sólo puede ser utilizado para tocar con los sonidos predefinidos en
él, porque no tiene la tecnología para conectarse mediante comunicación MIDI a una
computadora.
Aplicando la propuesta de este proyecto, agregando la tecnología MIDI, se podrá utilizar
programas para componer o para tocar con cualquier sonido que el usuario quiera definir.
Además demuestra que es más conveniente llevar a cabo esta idea por el bajo costo
económico que tiene, en comparación con el costo de comprar un teclado/piano con estas
características.

Introducción
Nuestra inspiración empezó cuando quisimos un controlador/piano midi como este:
Al ver los precios de estos, que van desde los 20.000 hasta los 60.000 pesos argentinos
aproximadamente, se nos ocurrió utilizar un piano eléctrico antiguo que tenía uno de los
integrantes y modificarlo para que haga lo mismo.
La idea es conectar nuestro piano eléctrico antiguo modificado para utilizarlo con cualquier
programa de PC para componer música, que contenga la posibilidad de conectar y utilizar
algún controlador MIDI.
El nombre del programa que vamos a utilizar es FL Studio 20, el cual tiene la siguiente
fachada.
Al tocar las teclas de nuestro piano las recibe la computadora, las muestra en los pianos de la
imagen y suena la nota que tocamos en específico.
Además podremos configurar en la pc para que las teclas de nuestro piano suenen como una
guitarra, bajo, sintetizadores, baterías y cualquier instrumento que exista.

Estos son los diferentes instrumentos que contiene este software.
También podremos grabar un sonido y hacer que ese sonido suene más grave o más agudo
dependiendo de la tecla del piano que se toque.
Le agregaremos la posibilidad a nuestro Piano MIDI de conectarse por bluetooth a nuestro
celular para poder así reproducir una demo automáticamente en la pc (es decir que se
“reproducen solas” las notas de una canción), prenderlo, apagarlo, subir y bajar la escala de
las notas (es decir que la nota que antes era un “Do3”, si bajamos la escala, ahora será un
“Do2” más grave, y si la subimos, ahora será un “Do4” más agudo).

Desarrollo técnico
Paso 1: Componentes
Para desarrollar este piano MIDI no se necesitan componentes costosos.
Componentes Utilizados:
● Arduino uno (13.50 US$)
● 74hc595 (encapsulado para comandar 8 salidas solo con 3 para arduino) (0.26 US$)
● Cables (1.00 US$)
● Placa Experimental Perforada (2.00 US$)
● Resistencias (1.00 US$)
● Estaño (2.00 US$)
● Módulo Bluetooth (6.50 US$)
● Piano Eléctrico que se quiera modificar (0.00 US$)
TOTAL: 26.26 US$ (7800 ARS aprox)
Dato: El proyecto costaría 5800 ARS si se desarrollara sin app de celular (al igual que los
comprados) por lo tanto nos ahorramos como mínimo 14200 ARS al hacerlo en vez de
comprarlo.

Paso 2: Desarrollo
Lo primero fue desarmar el piano, sacando los tornillos y la tapa, para
encontrar un bus de datos que es el componente a través del cual vamos a
identificar qué nota se está tocando.
Luego con un multímetro medimos entre los pines del bus de datos hasta identificar
todas las teclas del piano. Formando una matriz que indica, según los pares de pines
por los que pase la energía, qué tecla se está tocando.
Con este paso terminado, se diseñó el circuito para conectar el bus de datos con el arduino.
Mediante un circuito integrado (74HC595) se comandan ocho salidas, las que aparecen como
terminales rojas en la matriz anterior.
De esta manera se pueden enviar y recibir datos, con un programa elaborado en arduino, para
identificar y dirigir la o las teclas al software que permite componer música.

Circuito:
Posteriormente se elaboró el circuito y se soldó en una placa multipropósito.
UNIVERSIDAD BLAS PASCAL Córdoba, Argentina
LABORATORIO I 2022
Se diseñó y programó la aplicación para subir y bajar la escala y tocar una demo.
App:
Por último se programó en la IDE de arduino, enviando mediante comunicación serial las
notas con su intensidad a la computadora que permitió tocar y componer nuestra música.

Conclusiones y recomendaciones
Al hacer el proyecto concluimos en que hay una diferencia monetaria elevada en
comparación a si lo hubiéramos comprado nuevo. Concluyo también en que es un
proyecto que realmente voy a utilizarlo yo, David, para componer y tocar música y
creo que nos divertimos mucho haciéndolo. Así que si quieren un Piano MIDI en
algún momento les recomiendo plenamente que primero se fijen si no tienen un
teclado antiguo o roto que puedan usar.
Muchas Gracias.
![WhatsApp Image 2022-11-10 at 4 24 27 PM](https://github.com/msalamero/Proyectos-Arduino/assets/69313393/8b7f7933-749e-4b11-8e06-59cc4ad60587)
![WhatsApp Image 2022-11-13 at 5 28 44 PM](https://github.com/msalamero/Proyectos-Arduino/assets/69313393/a9ddbcd5-11a4-49f8-b25e-ca68d2cfed8a)
https://youtu.be/xXmdNATtreg
https://youtu.be/wXZrUMK7zxU
