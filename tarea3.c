#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>

typedef struct {

        int square[3][3]; // Matriz 3x3 que representa el tablero
        int x;    // Posición x del espacio vacío
        int y;    // Posición y del espacio vacío
        int nActions;

} State;

typedef struct Node {

        State state;
        struct Node* parent;

} Node;


void mostrarMenuPrincipal() {

        limpiarPantalla();
        puts("========================================\n");
        puts("     Escoge método de búsqueda\n");
        puts("========================================\n");

        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Salir\n");

}
int distancia_L1(State* state) {
    int ev=0;
    int k=1;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            int val=state->square[i][j];
            if (val==0) continue;
            int ii=(val)/3;
            int jj=(val)%3;
            ev+= abs(ii-i) + abs(jj-j);
        }
    return ev;
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


int main() {

        State estado_inicial = {
                {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
                 {1, 3, 4}, // Segunda fila
                 {6, 5, 7}, // Tercera fila
                 },  
                0, 0   // Posición del espacio vacío (fila 0, columna 1)
        };

        estado_inicial.nActions = 0;


        int opcion;
        int cont = 0;

        do {

                mostrarMenuPrincipal();
                printf("Ingrese su opción: ");
                scanf(" %d", &opcion);

                switch (opcion) {
                case 1:

                    dfs(estado_inicial, cont);
                    break;
                case 2:

                    bfs(estado_inicial, cont);
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
