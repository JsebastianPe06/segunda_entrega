# Especificaciones y Manual de Uso

## Descripción 

Este proyecto consiste en la simulación de una plataforma de streaming tipo
Netflix donde el objetivo es permitir un sistema de búqueda cuya eficacia
al buscar una película o serie sea los más cercando a complejidad temporal
O(1) sin tener que gastar tanta memoria.

## Módulos

- usuario.h: Una representación del usuario en la plataforma, con un nombre e
id  único que lo identifica.

- contenido.h: Una representación de las películas y series de la plataforma, con
id y nombre único que los representación.

- plataforma.h: El módulo principal que representa a la plataforma, con sus
métodos de búqueda, cargado y guardado de datos para el correcto funcionamiento.

## Librerías externas

### <Eigen/SparseCore>

Librería usada para la representación de las matrices dispersas usadas en el
programa. No hace falta instalarla y configurarla dado que ya está integrada en
el proyecto.

### <nlohmann/json.hpp>

Librería usada para trabajar con .json usados para guardar los datosque requiere
la plataforma para funcionar de manera correcta.  No hace falta instalarla y configurarla
dado que ya está integrada en el proyecto.

## Uso de .json

para simular el proceso de una plataforma donde no se pierdan los datos al cerrar
un programa lo que se hace es guardar la información en archivos.json de los cuales
se retorna la información cada vez que se abre el programa. Estos archivos no se
deben tocar dado que una pequeña modificación de los mismos puede generar un error.

## Interfaz gráfica

Una interfaz cuyo objetivo es mostrar de manera más eficaz como funcionan las
implementadas dentro del programa, se elaboró con gran apoyo de la IA y usando
Qt Creator, un programa que da grandes facilidades para la elaboración de
interfaces gráficas. La interfaz fue desarrollada usando Qt Widgets.

## Requerimentos

- Qt 6.5+ (se recomienda Qt 6.10 con MinGW 64-bit).

- Compilador MinGW incluido con Qt.

- CMake o qmake (si se compila fuera de Qt Creator).

- Visual Studio Code (opcional).

- Sistema operativo Windows 10 o 11.

Aclaración: las Librerías externas anteriormente mencionadas ya están implementadas
dentro del programa, no hace falta instalarlas.

## Forma de uso

### Ejecutado desde Qt Creator.

- Abrir la carpeta app_qt/.

- Cargar el archivo .pro.

- Presionar Run.

- La interfaz aparecerá automáticamente.

### Ejecutado desde VScode

Se requiere un CMakeLists.txt correctamente configurado, este proyecto inicialmente
está planteado para ser ejecutado en Qt Creator, pero si desea compilar y ejecutar
usando VScode con alguna terminal incorporada se recomienda configurar manualmente
el CMakeList.txt junto al task.json, launch.json y c_cpp_properties.json para
correcto funcionamiento.

## Guía de la interfaz

- El programa inicia con una espacio en el cual ingresa el nombre de un usuario
que si encuentra le permitirá ingresar a la plataforma.

- Dentro de la plataforma, el ususario tiene diferentes formas de búsqueda, además
de un recomendador que cambia dependiendo de lo que vé.

- Una vez encontrado un contenido a ver, el usuario puede seleccionar la opción
el contenido para entrar en un proceso de simulación de vista y para posteriormente
poder calificar dicho contenido, esta información quedará guardada en la matriz disperssa
que relaciona usuarios con contenido para cambiar la recomendación.

- Cuando el usuario cierra el programa todos los datos se guardan en los .json.

## Uso de IA

Estimamos aproximadamente un 40% de uso de IA, si bien esta se implementó muy
poco para el desarrollo de métodos y clases, hay 2 aspectos donde si se uso demasiado:

- Para establecer el correcto manejo de los archivo .json, dada una dificultad de
manejo de los mismo en c++.

- Para desarrollo de la interfaz gráfica dado que por falta de tiempo no se pudo
aprender a usar de manera adecuada las herramienta para el desarrollo de la misma.

Ya hablando de usos más secundarios la IA se usó para buscar bibliotecas externas
necesarias para el programa y para la solución de problemas al compilar y ejecutar.