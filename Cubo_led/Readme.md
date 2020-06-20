# Cubo Led
##By Godoy Matías y Marquez Federico
### Universidad Blas Pascal - Ing. Informática - Lab 1 - 2019
------------------------------------------------------------------------------------------
![01](images/1.png)

## Introducción
En este informe se va a mencionar el trabajo realizado de un proyecto sobre Arduino para la materia Laboratorio I, en la universidad Blas Pascal. El proyecto consiste en un Cubo Led 5x5x5, el cual su función es hacer luces mediante los leds formando figuras en el cubo.
Los proyectos desarrollados en los secundarios o universidades ayudan mucho al estudiante para profundizar los conceptos aprendidos durante el año, ya que es cuando se dan cuenta para que sirven dichos conceptos.
Nosotros elegimos hacer el Cubo Led 5x5x5 ya que representaba una dificultad elevada para nuestros conocimientos, donde se necesita creatividad para hacer la carcasa o base, manejo de los cables, lógica en las conexiones, conocimientos en soldadura con estaño o cautín y hasta en los códigos internos del Arduino. También vamos a mostrar los diferentes pasos para el armado, diferentes recomendaciones, problemas que se nos fueron dando, etcétera.

## Cubo Led 5x5x5

### ¿Cómo surgió la idea?
La idea surgió en un debate sobre el nivel de dificultad que queríamos manejar, ya que en ese momento no teníamos muchos conocimientos sobre el tema y teníamos un presupuesto bajo. 
Al principio se nos ocurrían un montón de ideas, como un vúmetro con una tira led donde principalmente lo que hacía era ir prendiendo los leds de la tira mediante la frecuencia que recibía de un micrófono. Pero llegamos a la conclusión de que no lo podíamos hacer por el elevado valor que tiene la tira led que necesitábamos. También se nos ocurrió hacer un Reloj de presentismo mediante huellas dactilares, pero teníamos el mismo problema que en el anterior, el elevado valor de los componentes que necesitábamos. Además, se nos ocurrían otras ideas como una alarma para despertador, una alarma para una puerta, donde tenía un sensor y si se abría la puerta avisaba al celular mediante wifi, entre otras cosas.
Así que terminamos decidiendo por el Cubo Led 5x5x5 ya que tiene un nivel de dificultad correcto para nosotros, no se necesitan componentes costosos y, sobre todo, se necesitaba la programación en los códigos internos de Arduino.

### Funcionamiento
La pregunta seria: ¿Qué es lo que hace?
Prácticamente lo que hace es prender y apagar los 125 leds con lo que está conformado para poder hacer formas en el cubo, es decir, que mediante la codificación interna del Arduino se pueden programar los leds para que se prendan recreando diferentes estilos de luces.
Con este proyecto seguro que vamos a sacar una sonrisa e incluso ver alguna cara de impresión al ver de qué es capaz, también por la cantidad de diseños y graficas que se pueden llegar a “dibujar”.

### Armado
* Materiales
Los materiales que nosotros usamos para poder armar el cubo Led 5x5x5 son:
Un Arduino Uno:  es una plataforma de creación de electrónica de código abierto, la cual está basada en hardware y software libre, fácil de utilizar para los creadores y desarrolladores. Los microcontroladores que contiene son circuitos integrados en los que se pueden grabar instrucciones, las cuales las escribes con el lenguaje de programación Arduino IDE. Estas instrucciones permiten crear programas que interactúan con los circuitos de la placa.
125 diodos leds: Los diodos son componentes electrónicos que permiten el paso de la corriente en un solo sentido, en sentido contrario no dejan pasar la corriente.
Un diodo Led es un diodo que además de permitir el paso de la corriente solo un sentido, en el sentido en el que la corriente pasa por el diodo, este emite luz.
Cables de conexión: El cable eléctrico es aquel cuyo propósito es conducir electricidad. Suele estar fabricado de cobre, por su nivel de conductividad, o de aluminio, que es más económico que el cobre.
Soldador con estaño o cautín:  En electrónica, el sistema más utilizado para garantizar la circulación de corriente entre los diferentes componentes de un circuito es la soldadura con estaño o aleaciones de este. Se consiguen uniones muy fiables y definitivas, que permiten además sujetar los componentes en su posición y soportan bastante bien los golpes y las vibraciones, asegurando la conexión eléctrica durante un tiempo prolongado.

* Armado
Para poder explicar el armado que hicimos lo vamos a mostrar con pasos:
Paso 1: En primer lugar, que hicimos fue soldar los 125 leds, para esto fuimos soldando 5 planchas de 25 leds.
Paso 2: Una vez que soldamos las 5 planchas, empezamos a soldar las 5 planchas, una arriba de la otra, quedando en forma de cubo.
Paso 3: Luego de tener el cubo con los leds soldados, empezamos a construir la caja donde va a ir apoyado. Para ello agarramos una caja y le hicimos los huecos correspondientes para que entre cada cátodo de los leds.
Paso 4: Después en cada plancha hay que soldar un cable en el ánodo de cualquier led.
Paso 5: A los cátodos de los leds que salen por debajo de la caja, insertados anteriormente, les conectamos un cable a cada uno. En total hay 25 cátodos, entonces habrá 25 cables conectados.
Paso 6: Se conectan todos los cables al Arduino.
Paso 7: Se ejecuta el código.

* Codificación
Para el funcionamiento del Cubo Led 5x5x5, se necesita un código de programación de Arduino. Dicho código se puede programar en programas como: Fritzing, Arduino Project Hub, Tinkercad, GitHub, entre otros.
En primer lugar, en nuestro código, se declaran las variables a utilizar. Nosotros las declaramos arreglos para que sea más fácil la programación.
Luego se inicializan las variables. Es decir, que se declaran las variables como salidas.
Por último, existen diferentes métodos o funciones:
El primero es el “Método Principal”: que como su nombre lo dice es la función esencial donde es la que se está ejecutando constantemente y es la que llama a los otros métodos.
Después existen otros métodos donde hacen que se prendan todos los leds, que se apaguen, de que hagan un barrido horizontal o vertical, de que los leds hagan un titileo, un espiral, entre otros.
Con esta codificación se pueden recrear diferentes estilos de luces, dejando al cubo muy agradable a la vista.

## Conclusión
Este proyecto nos permitió desarrollar tanto nuestras habilidades de construcción mecánica del cubo como nuestras habilidades "creativas", si bien el mismo fue una idea tomada de internet, nosotros debimos de crear patrones de luces con mucha prueba y error, como así también hacer nuestra construcción con nuestros conocimientos básicos, escasez de recursos y presupuesto. Gracias a este último punto, nos obligó a tener que pensar formas en la que construir el proyecto evitando tener que comprar algunos componentes en específico. También haber aprendido de solucionar diferentes problemas que se nos fueron surgiendo, haciendo el proyecto un poco más difícil y haber adquirido más conocimiento con esos errores.
Por último, queremos agradecemos a nuestros profesores de catedra por acompañarnos y ayudarnos en las dudas que tuvimos.
- Ing. Salamero Alejandro Martin
- Profesora Nano Mónica Liliana

![02](images/2.png)
