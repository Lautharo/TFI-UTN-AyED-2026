#include <stdio.h>
#include <stdlib.h>
#include "MENU.h"

int mostrarMenuPrincipal() {
    int opcion;
    system("cls");
    printf("=================================================\n");
    printf("      SISTEMA DE GESTION DE PERSONAL - YPF       \n");
    printf("=================================================\n\n");
    
    printf("1. Crear archivo (Reiniciar base de datos)\n");
    printf("2. Grabar informacion (Alta de Empleado)\n");
    printf("3. Baja Logica (Desactivar Empleado)\n");
    printf("4. Baja Fisica (Eliminar definitivamente)\n");
    printf("5. Modificacion de campos\n");
    printf("6. Listado de la informacion\n");
    printf("7. Consulta por clave (Legajo/DNI)\n");
    printf("8. Estructura Dinamica (Cargar a Lista/Arbol)\n");
    printf("0. Salir\n");
    
    printf("\n=================================================\n");
    printf("Ingrese su opcion: ");
    
    // Validacion por si escriben
    if (scanf("%d", &opcion) != 1) {
        while(getchar() != '\n');
        return -1;
    }
    
    return opcion;
}