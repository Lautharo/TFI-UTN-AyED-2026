#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "CAMPOS.h"
#include "MENU.h" 

// --- HERRAMIENTAS VISUALES LOCALES ---
void gotoXY_fisica(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_fisica(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Dibujamos la ficha para que sepa a quien va a matar
void dibujarFichaEliminar(reg r, int yInicio) {
    int x = 30;
    
    color_fisica(0x1F); // Azul fondo
    gotoXY_fisica(x, yInicio);     printf("Nombre:   %s", r.nombreapell);
    gotoXY_fisica(x, yInicio + 2); printf("Puesto:   %s", r.puesto);
    gotoXY_fisica(x, yInicio + 4); printf("Area:     %s", r.area);
    
    // ESTADO ACTUAL
    gotoXY_fisica(x + 40, yInicio); 
    if(r.activo) {
        color_fisica(0x2F); // Verde
        printf(" [ ESTADO: ACTIVO ] ");
    } else {
        color_fisica(0x4F); // Rojo
        printf(" [ ESTADO: INACTIVO ] ");
    }
}

void realizarBajaFisica()
{
    reg r;
    FILE *m, *aux;
    int legajoBuscado;
    bool encontrado = false;
    char confirmacion;

    // Abrimos el original para leer
    m = fopen("campos.dat", "rb");

    if (m == NULL) {
        system("cls");
        color_fisica(0x4F);
        printf("\n [ERROR]: No se pudo abrir la base de datos.\n");
        getch();
        return;
    }

    // --- INTERFAZ ---
    system("cls");
    color_fisica(0x1F); 
    
    // Marco
    for(int i=2; i<118; i++) { gotoXY_fisica(i, 2); printf("%c", 205); gotoXY_fisica(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_fisica(2, i); printf("%c", 186); gotoXY_fisica(118, i); printf("%c", 186); }
    gotoXY_fisica(2, 2); printf("%c", 201); gotoXY_fisica(118, 2); printf("%c", 187);
    gotoXY_fisica(2, 28); printf("%c", 200); gotoXY_fisica(118, 28); printf("%c", 188);

    // Titulo (ROJO PARA ALERTAR)
    color_fisica(0x4F); // Fondo Rojo, Letra Blanca
    gotoXY_fisica(40, 4); printf("=== BAJA FISICA (ELIMINAR DEFINITIVAMENTE) ===");
    
    // Input
    color_fisica(0x1F);
    gotoXY_fisica(30, 8); printf("Ingrese LEGAJO a eliminar: ");
    
    color_fisica(0x1B); 
    printf("[      ]");
    gotoXY_fisica(59, 8); 
    
    scanf("%d", &legajoBuscado);

    // 1. BUSCAR PRIMERO (Para mostrarlo y preguntar)
    fread(&r, sizeof(struct reg), 1, m);
    while(!feof(m) && !encontrado) {
        if(r.legajo == legajoBuscado) {
            encontrado = true;
            
            // Mostrar victima
            color_fisica(0x1E); // Amarillo
            gotoXY_fisica(30, 11); printf("--- ATENCION: REGISTRO A ELIMINAR ---");
            dibujarFichaEliminar(r, 13);
            
            // Advertencia final
            color_fisica(0x4E); // Fondo Rojo, Letra Amarilla (Peligro)
            gotoXY_fisica(30, 20); printf(" ADVERTENCIA: Esta accion NO se puede deshacer. ");
            
            // Pregunta
            color_fisica(0x1F);
            gotoXY_fisica(30, 22); printf("Confirma la eliminacion TOTAL de este empleado? (s/n): ");
            confirmacion = getch();
        }
        fread(&r, sizeof(struct reg), 1, m);
    }

    // Si no lo encontro, cerramos y nos vamos
    if(!encontrado) {
        fclose(m);
        color_fisica(0x4F);
        gotoXY_fisica(40, 15); printf(" NO SE ENCONTRO EL LEGAJO %d ", legajoBuscado);
        gotoXY_fisica(40, 26); printf("Presione una tecla para volver...");
        getch();
        return;
    }

    // 2. SI CONFIRMO, HACEMOS LA COPIA
    if(confirmacion == 's' || confirmacion == 'S') {
        // Rebobinamos el original
        rewind(m);
        
        // Creamos el auxiliar
        aux = fopen("temp.dat", "wb");
        
        if (aux == NULL) {
            fclose(m);
            printf("Error creando archivo temporal.");
            return;
        }

        // COPIAR TODOS MENOS EL BORRADO
        fread(&r, sizeof(struct reg), 1, m);
        while(!feof(m)) {
            if(r.legajo != legajoBuscado) {
                fwrite(&r, sizeof(struct reg), 1, aux);
            }
            fread(&r, sizeof(struct reg), 1, m);
        }
        
        fclose(m);
        fclose(aux);
        
        // ELIMINAR VIEJO Y RENOMBRAR NUEVO
        remove("campos.dat");
        rename("temp.dat", "campos.dat");
        
        color_fisica(0x2F); // Verde
        gotoXY_fisica(35, 24); printf(" REGISTRO ELIMINADO FISICAMENTE CON EXITO ");
    } 
    else {
        fclose(m);
        color_fisica(0x1F);
        gotoXY_fisica(35, 24); printf(" Operacion cancelada. El registro esta a salvo. ");
    }

    // Mensaje Salida
    const char* msj = "Presione una tecla para volver al Menu...";
    color_fisica(0x9F); 
    gotoXY_fisica((120 - strlen(msj))/2, 26); 
    printf("%s", msj);
    
    getch();
}