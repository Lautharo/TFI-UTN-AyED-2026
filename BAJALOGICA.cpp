#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "CAMPOS.h"
#include "MENU.h" 

// --- HERRAMIENTAS VISUALES LOCALES ---
void gotoXY_baja(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_baja(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Dibuja la ficha de datos del empleado encontrado
void dibujarFichaEmpleado(reg r, int yInicio) {
    int x = 30; // Margen izquierdo de la ficha
    
    color_baja(0x1F); // Azul fondo
    gotoXY_baja(x, yInicio);     printf("Nombre:   %s", r.nombreapell);
    gotoXY_baja(x, yInicio + 2); printf("Puesto:   %s", r.puesto);
    gotoXY_baja(x, yInicio + 4); printf("Area:     %s", r.area);
    gotoXY_baja(x, yInicio + 6); printf("Turno:    %s", r.turno);
    
    // ESTADO (Visualmente impactante)
    gotoXY_baja(x + 40, yInicio); 
    if(r.activo) {
        color_baja(0x2F); // Fondo Verde
        printf(" [ ACTIVO ] ");
    } else {
        color_baja(0x4F); // Fondo Rojo
        printf(" [ INACTIVO ] ");
    }
}

void realizarBajaLogica()
{
    reg r;
    FILE *m;
    int legajoBuscado;
    bool encontrado = false;
    char confirmacion;

    // ABRIMOS EN MODO "r+b" (Lectura y Escritura) para poder modificar
    m = fopen("campos.dat", "r+b");

    if (m == NULL) {
        system("cls");
        color_baja(0x4F);
        printf("\n [ERROR]: No se pudo abrir la base de datos. Cargue empleados primero.\n");
        getch();
        return;
    }

    // --- INTERFAZ DE BUSQUEDA ---
    system("cls");
    color_baja(0x1F); 
    
    // Marco Principal
    for(int i=2; i<118; i++) { gotoXY_baja(i, 2); printf("%c", 205); gotoXY_baja(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_baja(2, i); printf("%c", 186); gotoXY_baja(118, i); printf("%c", 186); }
    gotoXY_baja(2, 2); printf("%c", 201); gotoXY_baja(118, 2); printf("%c", 187);
    gotoXY_baja(2, 28); printf("%c", 200); gotoXY_baja(118, 28); printf("%c", 188);

    // Titulo
    color_baja(0x1E); // Amarillo
    gotoXY_baja(40, 4); printf("=== BAJA LOGICA (DESACTIVAR) ===");
    
    // Input de Busqueda
    color_baja(0x1F);
    gotoXY_baja(30, 8); printf("Ingrese LEGAJO a buscar: ");
    
    color_baja(0x1B); // Cyan para el input
    printf("[      ]");
    gotoXY_baja(57, 8); // Poner cursor dentro de corchetes
    
    scanf("%d", &legajoBuscado);

    // --- BUSCAR EN ARCHIVO ---
    fread(&r, sizeof(struct reg), 1, m);
    while(!feof(m) && !encontrado) {
        if(r.legajo == legajoBuscado) {
            encontrado = true;
            
            // DIBUJAR RESULTADO
            color_baja(0x1E); // Titulo Ficha
            gotoXY_baja(30, 11); printf("--- DATOS DEL EMPLEADO ---");
            
            dibujarFichaEmpleado(r, 13);
            
            // LOGICA DE BAJA
            if(r.activo == false) {
                // Ya estaba dado de baja
                color_baja(0x4F); // Rojo
                gotoXY_baja(35, 22); printf(" ESTE EMPLEADO YA ESTA DADO DE BAJA ");
            } 
            else {
                // Preguntar confirmacion
                color_baja(0x1E); // Amarillo alerta
                gotoXY_baja(30, 22); printf("Desea dar de baja a este empleado? (s/n): ");
                confirmacion = getch();
                
                if(confirmacion == 's' || confirmacion == 'S') {
                    r.activo = false; // LA MAGIA: Cambiamos el estado
                    
                    // Retrocedemos el puntero un lugar para sobrescribir
                    fseek(m, -sizeof(struct reg), SEEK_CUR);
                    fwrite(&r, sizeof(struct reg), 1, m);
                    
                    color_baja(0x2F); // Verde Exito
                    gotoXY_baja(35, 24); printf(" BAJA LOGICA REALIZADA CON EXITO ");
                } else {
                    color_baja(0x1F);
                    gotoXY_baja(35, 24); printf(" Operacion cancelada por el usuario. ");
                }
            }
        }
        fread(&r, sizeof(struct reg), 1, m);
    }

    if(!encontrado) {
        color_baja(0x4F); // Rojo Error
        gotoXY_baja(40, 15); printf(" NO SE ENCONTRO EL LEGAJO %d ", legajoBuscado);
    }

    fclose(m);

    // Mensaje Salida
    const char* msj = "Presione una tecla para volver al Menu...";
    color_baja(0x9F); 
    gotoXY_baja((120 - strlen(msj))/2, 26); 
    printf("%s", msj);
    
    getch();
}