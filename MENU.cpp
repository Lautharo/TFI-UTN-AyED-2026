#include <stdio.h>
#include <stdlib.h>
#include "MENU.h"

int mostrarMenuPrincipal() {
    int opcion;
    
    // Configurar color de consola: 1 (Azul), F (Blanco Brillante) -> Estilo YPF
    system("color 1F"); 
    
    system("cls");
    
    // LOGO ASCII ART DE YPF
    printf("\n");
    printf("  __   __  _____   _____ \n");
    printf("  \\ \\ / / |  __ \\ |  ___|\n");
    printf("   \\ V /  | |__) || |__  \n");
    printf("    | |   |  ___/ |  __| \n");
    printf("    | |   | |     | |    \n");
    printf("    |_|   |_|     |_|    \n");
    printf("\n");
    printf("=========================================================\n");
    printf("       SISTEMA DE GESTION DE PERSONAL - TFI 2026         \n");
    printf("=========================================================\n\n");
    
    printf("  1. Crear archivo (Reiniciar base de datos)\n");
    printf("  2. Grabar informacion (Alta de Empleado)\n");
    printf("  3. Baja Logica (Desactivar Empleado)\n");
    printf("  4. Baja Fisica (Eliminar definitivamente)\n");
    printf("  5. Modificacion de campos\n");
    printf("  6. Listado de la informacion\n");
    printf("  7. Consulta por clave (Legajo/DNI)\n");
    printf("  8. Crear estructura dinamica (Cargar en Memoria)\n");
    printf("  9. Mostrar datos de la estructura dinamica\n");
    printf("  0. Salir\n");
    
    printf("\n=========================================================\n");
    printf("  Ingrese su opcion: ");
    
    // Validacion para evitar bucles infinitos si meten letras
    if (scanf("%d", &opcion) != 1) {
        while(getchar() != '\n'); // Limpiar el buffer de teclado
        return -1;
    }
    
    return opcion;
}