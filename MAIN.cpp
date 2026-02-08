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
#include "CONSULTA.h"
#include "ARBOL.h"
#include "MODIFICAR.h"

int main() {
    int opc;
    char usuarioActual[11]; 
    // --- PASO 1: LOGIN ---
    if (iniciarSesion(usuarioActual) == false) {
        return 0;
    }
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
                mostrarPantallaCarga("ACCEDIENDO AL MODULO DE BAJAS...");
                realizarBajaLogica();
                break;
            case 4:
                mostrarPantallaCarga("ACCEDIENDO AL MODULO DE ELIMINACION...");              
                realizarBajaFisica();
                break;
            case 5:
                mostrarPantallaCarga("ACCEDIENDO A MODIFICACIONES...");
                realizarModificacion();
                break;
            case 6:
                mostrarPantallaCarga("ACCEDIENDO AL LISTADO...");
                realizarListaInfo();
                break;
            case 7:
                mostrarPantallaCarga("BUSCANDO EN LA BASE DE DATOS...");
                realizarConsulta();
                break;
            case 8:
                mostrarPantallaCarga("CARGANDO DATOS EN MEMORIA...");
                cargarArbolEnMemoria();
                break;
            case 9:
                mostrarArbolOrdenado();
                break;
            case 0:
                mostrarSalida();
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }

    } while (opc != 0);

    return 0;
}