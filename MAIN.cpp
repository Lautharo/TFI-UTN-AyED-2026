// MAIN.cpp
#include <stdio.h>
#include <stdlib.h>
#include "MENU.h"    
#include "USUARIO.h" 
#include "CAMPOS.h"
#include "ALTA.h"
#include "BAJALOGICA.h"
#include "BAJAFISICA.h"
#include "LISTAINFO.h"

int main() {
    int opc;

    // --- PASO 1: LOGIN / REGISTRO ---
    // Por ahora, llamamos directo a registrar para probar tu codigo.
    // En el futuro, aca iria un "iniciarSesion()".
    regUser(); 

    // --- PASO 2: SISTEMA PRINCIPAL ---
    do {
        opc = mostrarMenuPrincipal();

        switch(opc) {
            case 1:
            	mostrarPantallaCarga("INICIANDO MODULO...");
			    carga_empleados();
			    break;
			case 2:
			    mostrarPantallaCarga("ACCEDIENDO AL SISTEMA DE ALTA...");
			    grabarInformacion(); 
			    break;
            case 3:
                printf("\n[3] Baja Logica seleccionada...\n");
                system("pause");
            	system("cls");
                void realizarBajaLogica();
                break;
            case 4:
                printf("\n[4] Baja Fisica seleccionada...\n");
                system("pause");
            	system("cls");                
                realizarBajaFisica();
                break;
            case 5:
                printf("\n[5] Modificar datos...\n");
                break;
            case 6:
                printf("\n[6] Listado general...\n");
                system("pause");
            	system("cls");
                void realizarListaInfo();
                break;
            case 7:
                printf("\n[7] Consulta particular...\n");
                break;
            case 8:
                printf("\n[8] Creando Arbol/Lista en memoria...\n");
                break;
            case 9:
            	printf("\n[9] Mostrando estructura dinamica...\n");
            case 0:
                printf("\nSaliendo del sistema YPF. Guardando datos...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }

    } while (opc != 0);

    return 0;
}