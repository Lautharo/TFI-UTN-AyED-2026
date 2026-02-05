#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "CAMPOS.h"
#include "MENU.h" 

// --- HERRAMIENTAS VISUALES LOCALES ---
void gotoXY_consulta(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_consulta(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Dibujamos una ficha detallada y elegante
void dibujarFichaConsulta(reg r) {
    int x = 30;
    int y = 12;
    
    // Caja contenedora de la ficha
    color_consulta(0x1F); // Azul
    // Bordes simples para la ficha interna
    for(int i=x-2; i<x+55; i++) { gotoXY_consulta(i, y-1); printf("%c", 196); gotoXY_consulta(i, y+9); printf("%c", 196); }
    
    // DATOS
    color_consulta(0x1F); // Blanco sobre Azul
    gotoXY_consulta(x, y);     printf("NOMBRE:    %s", r.nombreapell);
    gotoXY_consulta(x, y + 2); printf("LEGAJO:    %d", r.legajo);
    gotoXY_consulta(x, y + 4); printf("EDAD:      %d anios", r.edad);
    gotoXY_consulta(x, y + 6); printf("SUELDO:    $%d", r.sueldo);
    
    // Columna Derecha
    gotoXY_consulta(x + 30, y);     printf("PUESTO:  %s", r.puesto);
    gotoXY_consulta(x + 30, y + 2); printf("AREA:    %s", r.area);
    gotoXY_consulta(x + 30, y + 4); printf("TURNO:   %s", r.turno);
    gotoXY_consulta(x + 30, y + 6); printf("SEXO:    %s", r.sexo);
    
    // ESTADO
    gotoXY_consulta(x, y + 11); 
    printf("ESTADO ACTUAL: ");
    if(r.activo) {
        color_consulta(0x2F); // Fondo Verde
        printf(" [ ACTIVO ] ");
    } else {
        color_consulta(0x4F); // Fondo Rojo
        printf(" [ BAJA LOGICA / INACTIVO ] ");
    }
}

void realizarConsulta()
{
    reg r;
    FILE *m;
    int legajoBuscado;
    bool encontrado = false;

    m = fopen("campos.dat", "rb"); // Solo lectura ("rb")

    if (m == NULL) {
        system("cls");
        color_consulta(0x4F);
        printf("\n [ERROR]: No se pudo abrir la base de datos.\n");
        getch();
        return;
    }

    // --- INTERFAZ ---
    system("cls");
    color_consulta(0x1F); 
    
    // Marco
    for(int i=2; i<118; i++) { gotoXY_consulta(i, 2); printf("%c", 205); gotoXY_consulta(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_consulta(2, i); printf("%c", 186); gotoXY_consulta(118, i); printf("%c", 186); }
    gotoXY_consulta(2, 2); printf("%c", 201); gotoXY_consulta(118, 2); printf("%c", 187);
    gotoXY_consulta(2, 28); printf("%c", 200); gotoXY_consulta(118, 28); printf("%c", 188);

    // Titulo
    color_consulta(0x1E); // Amarillo
    gotoXY_consulta(42, 4); printf("=== CONSULTA PARTICULAR (POR LEGAJO) ===");
    
    // Input
    color_consulta(0x1F);
    gotoXY_consulta(30, 7); printf("Ingrese LEGAJO a consultar: ");
    
    color_consulta(0x1B); 
    printf("[      ]");
    gotoXY_consulta(59, 7); 
    
    scanf("%d", &legajoBuscado);

    // --- BUSQUEDA ---
    fread(&r, sizeof(struct reg), 1, m);
    while(!feof(m) && !encontrado) {
        if(r.legajo == legajoBuscado) {
            encontrado = true;
            
            // Si lo encuentra, mostramos la ficha linda
            color_consulta(0x1E); 
            gotoXY_consulta(30, 10); printf("--- FICHA DEL EMPLEADO ---");
            
            dibujarFichaConsulta(r);
        }
        fread(&r, sizeof(struct reg), 1, m);
    }

    if(!encontrado) {
        color_consulta(0x4F); // Rojo
        gotoXY_consulta(35, 15); printf(" NO SE ENCONTRO NINGUN EMPLEADO CON LEGAJO %d ", legajoBuscado);
    }

    fclose(m);

    // Mensaje Salida
    const char* msj = "Presione una tecla para volver al Menu...";
    color_consulta(0x9F); 
    gotoXY_consulta((120 - strlen(msj))/2, 26); 
    printf("%s", msj);
    
    getch();
}