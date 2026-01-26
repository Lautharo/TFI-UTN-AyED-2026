// MAIN.cpp
#include <stdio.h>
#include <stdlib.h>
#include "MENU.h"     // Tu nuevo menu
#include "USUARIO.h"  // Tu codigo de validacion

int main() {
    int opc;

    // --- PASO 1: LOGIN / REGISTRO ---
    // Por ahora, llamamos directo a registrar para probar tu codigo.
    // En el futuro, aca iria un "iniciarSesion()".
    registrarUsuario(); 

    // --- PASO 2: SISTEMA PRINCIPAL ---
    do {
        opc = mostrarMenuPrincipal();

        switch(opc) {
            case 1:
                printf("\n[Opcion 1] Crear archivo seleccionado...\n");
                // crearArchivo();
                break;
            case 2:
                printf("\n[Opcion 2] Alta de empleado seleccionada...\n");
                // altaEmpleado();
                break;
            case 3:
                printf("\n[Opcion 3] Baja Logica seleccionada...\n");
                break;
            case 4:
                printf("\n[Opcion 4] Baja Fisica seleccionada...\n");
                break;
            case 5:
                printf("\n[Opcion 5] Modificar datos...\n");
                break;
            case 6:
                printf("\n[Opcion 6] Listado general...\n");
                break;
            case 7:
                printf("\n[Opcion 7] Consulta particular...\n");
                break;
            case 8:
                printf("\n[Opcion 8] Estructuras Dinamicas...\n");
                break;
            case 0:
                printf("\nSaliendo del sistema. Guardando datos...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }
        
        if (opc != 0) {
            system("pause");
        }

    } while (opc != 0);

    return 0;
}