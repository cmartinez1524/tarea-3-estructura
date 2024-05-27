

Para ejecutar la tarea3 primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c tarea3.c -Wno-unused-result -o tarea3
````

Y luego ejecutar:
````
./tarea3
````

2. Opciones que Funcionan Correctamente y las que No Funcionan Correctamente
Búsqueda en Profundidad (Opción 1):

Realiza una búsqueda en profundidad para resolver el puzzle.
Limita el número de movimientos a 15 para evitar búsquedas excesivamente profundas.
Muestra los pasos desde el estado inicial hasta el estado final si encuentra una solución.
Búsqueda en Anchura (Opción 2):

Realiza una búsqueda en anchura para resolver el puzzle.
Limita el número de iteraciones a 15,000,000 para evitar largos tiempos de ejecución.
Muestra los pasos desde el estado inicial hasta el estado final si encuentra una solución.
Salir (Opción 3):

Finaliza el programa.
Opciones que No Funcionan Correctamente
Hasta el momento, todas las opciones implementadas funcionan correctamente.


3. Ejemplo Mostrando Cómo Interactuar con la Aplicación
Ejemplo de Ejecución
Al iniciar el programa, verá el siguiente menú:
````
========================================
          BIENVENIDO AL MENU           
========================================

     Escoge método de búsqueda

========================================

1) Búsqueda en Profundidad
2) Búsqueda en Anchura
3) Salir

========================================
Por favor, ingrese su elección (1-3): 

````
Por favor, ingrese su elección (1-3): 1

````
Estado Original:

x 2 8 
1 3 4 
6 5 7 

¡Puzzle resuelto!
Iteraciones: 4

Estado Inicial:

x 2 8 
1 3 4 
6 5 7 

Paso 3:

1 x 8 
6 2 4 
7 3 5 

Paso 2:

1 2 8 
x 3 4 
6 5 7 

Paso 1:

x 2 8 
1 3 4 
6 5 7 

````
Opción 2: Búsqueda en Anchura
````
Por favor, ingrese su elección (1-3): 2

Estado Inicial:

x 2 8 
1 3 4 
6 5 7 

¡Puzzle resuelto!
Iteraciones: 5

Estado Inicial:

x 2 8 
1 3 4 
6 5 7 

Paso 4:

1 x 8 
6 2 4 
7 3 5 

Paso 3:

1 2 8 
x 3 4 
6 5 7 

Paso 2:

x 2 8 
1 3 4 
6 5 7 

````
Opción 3: Salir
````
Por favor, ingrese su elección (1-3): 3
Saliendo del programa...

````