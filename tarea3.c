#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>

// Estructura que representa el estado del tablero
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;            // Coordenada x del espacio vacío
    int y;            // Coordenada y del espacio vacío
    int nActions;     // Número de acciones realizadas
} State;

// Estructura que representa un nodo en el árbol de búsqueda
typedef struct Node {
    State state;           // Estado del nodo
    struct Node* parent;   // Puntero al nodo padre
} Node;

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("          BIENVENIDO AL MENU           ");
    puts("========================================\n");
    puts("     Escoge método de búsqueda\n");
    puts("========================================\n");

    puts("1) Búsqueda en Profundidad");
    puts("2) Búsqueda en Anchura");
    puts("3) Salir\n");

    puts("========================================");
    printf("Por favor, ingrese su elección (1-3): ");
}

// Función que calcula la distancia L1 (Manhattan) para un estado dado
int calcularDistanciaManhattan(State* state) {
    int ev = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int val = state->square[i][j];
            if (val == 0) continue;
            int ii = val / 3;
            int jj = val % 3;
            ev += abs(ii - i) + abs(jj - j);
        }
    }
    return ev;
}

// Función que verifica si un movimiento es válido
int esMovimientoValido(int x, int y) { 
    return (x >= 0 && x < 3 && y >= 0 && y < 3); 
}

// Función que verifica si el estado actual es el estado final
int esEstadoFinal(const State* estado) {
    State estadoFinal = {
        {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}},
        0, 0
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] != estadoFinal.square[i][j])
                return 0;
        }
    }
    return 1;
}

// Función que copia un estado en otro
void copiarEstado(State original, State* nuevo) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            nuevo->square[i][j] = original.square[i][j];

    nuevo->x = original.x;
    nuevo->y = original.y;
    nuevo->nActions = original.nActions;
}

// Función que realiza un movimiento en el estado actual
void moverEspacio(State* current, int opcion) {
    int x = current->x;
    int y = current->y;
    int temp;

    switch (opcion) {
        case 1: // Mover espacio vacío hacia arriba
            if (esMovimientoValido(x, y - 1)) {
                temp = current->square[x][y - 1];
                current->square[x][y - 1] = current->square[x][y];
                current->square[x][y] = temp;
                current->y = y - 1;
            }
            break;
        case 2: // Mover espacio vacío hacia abajo
            if (esMovimientoValido(x, y + 1)) {
                temp = current->square[x][y + 1];
                current->square[x][y + 1] = current->square[x][y];
                current->square[x][y] = temp;
                current->y = y + 1;
            }
            break;
        case 3: // Mover espacio vacío hacia la izquierda
            if (esMovimientoValido(x - 1, y)) {
                temp = current->square[x - 1][y];
                current->square[x - 1][y] = current->square[x][y];
                current->square[x][y] = temp;
                current->x = x - 1;
            }
            break;
        case 4: // Mover espacio vacío hacia la derecha
            if (esMovimientoValido(x + 1, y)) {
                temp = current->square[x + 1][y];
                current->square[x + 1][y] = current->square[x][y];
                current->square[x][y] = temp;
                current->x = x + 1;
            }
            break;
    }
}

// Función para imprimir el estado del puzzle
void imprimirEstado(const State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
}

// Función que realiza la transición de un estado a otro
State* transicionEstado(State* estadoViejo, int accion) {
    State *estadoNuevo = (State*) malloc(sizeof(State));
    copiarEstado(*estadoViejo, estadoNuevo);
    moverEspacio(estadoNuevo, accion);
    estadoNuevo->nActions++;
    return estadoNuevo;
}

// Función que obtiene los nodos adyacentes para un nodo dado
List *obtenerNodosAdyacentes(Node* nodoPadre) {
    List *listaAdyacentes = list_create();
    int x = nodoPadre->state.x;
    int y = nodoPadre->state.y;

    for (int i = 1; i <= 4; i++) {
        State *nuevoEstado = transicionEstado(&nodoPadre->state, i);

        if (nuevoEstado->x != x || nuevoEstado->y != y) {
            Node *nuevoNodo = (Node*) malloc(sizeof(Node));
            nuevoNodo->state = *nuevoEstado;
            nuevoNodo->parent = nodoPadre;
            list_pushBack(listaAdyacentes, nuevoNodo);
        } else {
            free(nuevoEstado);
        }
    }
    return listaAdyacentes;
}

// Función que realiza la búsqueda en profundidad (DFS)
void busquedaEnProfundidad(State estadoInicial, int conteo) {
    Stack* pila = stack_create(pila);
    printf("\nEstado Original:\n\n");
    imprimirEstado(&estadoInicial);
    printf("\n");

    Node *raiz = (Node *) malloc(sizeof(Node));
    raiz->parent = NULL;
    raiz->state = estadoInicial;
    stack_push(pila, raiz);

    while (list_size(pila) > 0) {
        Node *nodoActual = (Node *) stack_top(pila);
        stack_pop(pila);

        if (nodoActual->state.nActions >= 15)
            continue;

        if (esEstadoFinal(&nodoActual->state)) {
            printf("¡Puzzle resuelto!\n");
            printf("Iteraciones: %d\n\n", conteo);

            Node *nodo = nodoActual;
            int pasos = nodoActual->state.nActions;

            while (nodo != NULL) {
                if (pasos == 0)
                    printf("Estado Inicial:\n\n");
                else
                    printf("Paso %d:\n\n", pasos);

                imprimirEstado(&nodo->state);
                printf("\n");

                nodo = nodo->parent;
                pasos--;
            }

            stack_clean(pila);
            free(nodo);

            return;
        }

        List *nodosAdyacentes = obtenerNodosAdyacentes(nodoActual);
        void *aux = list_first(nodosAdyacentes);

        while (aux != NULL) {
            stack_push(pila, aux);
            aux = list_next(nodosAdyacentes);
        }

        list_clean(nodosAdyacentes);
        conteo++;
    }

    printf("No se encontró la solución dentro del rango limitado.\n");
    stack_clean(pila);
}

// Función que realiza la búsqueda en anchura (BFS)
void busquedaEnAnchura(State estadoInicial, int conteo) {
    Queue* cola = queue_create(cola);
    printf("Estado Inicial:\n\n");
    imprimirEstado(&estadoInicial);
    printf("\n");

    Node *raiz = (Node *) malloc(sizeof(Node));
    raiz->parent = NULL;
    raiz->state = estadoInicial;
    queue_insert(cola, raiz);

    while (list_size(cola) > 0) {
        Node *nodoActual = (Node *) queue_front(cola);
        queue_remove(cola);

        if (conteo >= 15000000) {
            printf("Proceso terminado: Límite de iteraciones alcanzado (15.000.000)\n");
            return;
        }

        if (esEstadoFinal(&nodoActual->state)) {
            printf("¡Puzzle resuelto!\n");
            printf("Iteraciones: %d\n\n", conteo);

            Node *nodo = nodoActual;
            int pasos = nodoActual->state.nActions;

            while (nodo != NULL) {
                if (pasos == 0)
                    printf("Estado Inicial:\n\n");
                else
                    printf("Paso %d:\n\n", pasos);

                imprimirEstado(&nodo->state);
                printf("\n");

                nodo = nodo->parent;
                pasos--;
            }

            queue_clean(cola);
            free(nodo);

            return;
        }

        List *nodosAdyacentes = obtenerNodosAdyacentes(nodoActual);
        void *aux = list_first(nodosAdyacentes);

        while (aux != NULL) {
            queue_insert(cola, aux);
            aux = list_next(nodosAdyacentes);
        }

        list_clean(nodosAdyacentes);
        conteo++;
    }

    printf("No se encontró la solución.\n");
    queue_clean(cola);
}

// Función principal
int main() {
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}}, // Tercera fila
        0, 0 // Posición del espacio vacío (fila 0, columna 0)
    };

    estado_inicial.nActions = 0;

    int opcion;
    int cont = 0;

    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                busquedaEnProfundidad(estado_inicial, cont);
                break;
            case 2:
                busquedaEnAnchura(estado_inicial, cont);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (opcion != 3);

    return 0;
}
