#include <stdio.h>
#include <stdlib.h>
#include "MENU.h" // Incluimos su propia cabecera

int mostrarMenu() {
    int opc;
    printf("1. Opcion Uno\n");
    printf("2. Opcion Dos\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opc);
    return opc;
}