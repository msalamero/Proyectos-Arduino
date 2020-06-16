# Tanque de Agua Sensorizado
## By Moyano Franco y Abeijon Diego
-----------------------------------------------------------------------------------------------
## Introducción
El presente informe, junto con las hojas de datos adjuntas, pretende
demostrar el desarrollo del proyecto llevado a cabo en la materia Técnicas Digitales 2,
dictada por los profesores Salamero Martín y Escudero Javier.
El proyecto en general es un trabajo conjunto con otros grupos, encargados
de la domotización de diferentes sectores del hogar. El objetivo que se nos ha asignado
como equipo en particular es lograr medir la cantidad de litros que tiene el tanque de
agua de la casa, la temperatura del agua, la temperatura del ambiente exterior al tanque
y la presencia o no de presión de agua justo antes del ingreso a dicho tanque.
A través del informe se explicarán las tareas ejecutadas para llegar a la
realización del sistema domotizado, tales como la conexión con el servidor elegido por
el profesor y la programación de los sensores.

## La placa de desarrollo

CU ESP-32S de Zerynth la cual es programable mediante la interfase de
programación de la placa Arduino con el mismo lenguaje de programación.
La placa utilizada contiene integrado un módulo de WiFi el cual permite
programar directamente el enlace al servidor sin la necesidad de configurar pines para
un módulo externo.
A continuación, se muestra la configuración de los pines de la placa
NodeMCU ESP-32S.
