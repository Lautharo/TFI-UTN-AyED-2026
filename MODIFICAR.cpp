#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>
#include "CAMPOS.h" 
#include "MENU.h"   

// --- HERRAMIENTAS VISUALES LOCALES ---
void gotoXY_mod(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_mod(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Función auxiliar para limpiar la zona de abajo antes de escribir
void limpiarZonaInput() {
    color_mod(0x1F);
    gotoXY_mod(30, 24); 
    printf("                                                     "); // Borra la linea
    gotoXY_mod(30, 24); // Vuelve el cursor al inicio
}

// Muestra los datos actuales
void mostrarDatosActuales(reg r) {
    color_mod(0x1F); // Azul fondo
    // Limpiamos la zona de datos antes de escribir para evitar basura
    for(int y=10; y<=18; y+=2) {
        gotoXY_mod(30, y); printf("                                                  ");
    }
    
    gotoXY_mod(30, 10); printf("1. Nombre:    %s", r.nombreapell);
    gotoXY_mod(30, 12); printf("2. Puesto:    %s", r.puesto);
    gotoXY_mod(30, 14); printf("3. Area:      %s", r.area);
    gotoXY_mod(30, 16); printf("4. Turno:     %s", r.turno);
    gotoXY_mod(30, 18); printf("5. Sueldo:    $%d", r.sueldo);
    
    color_mod(0x1E); // Amarillo
    gotoXY_mod(30, 22); printf("0. SALIR / CANCELAR");
}

void realizarModificacion()
{
    reg r;
    FILE *m;
    int legajoBuscado;
    bool encontrado = false;
    int opcion = -1;

    m = fopen("campos.dat", "r+b");

    if (m == NULL) {
        system("cls");
        printf("Error: No se encuentra 'campos.dat'.");
        getch();
        return;
    }

    // --- BUSQUEDA ---
    system("cls");
    color_mod(0x1F);
    
    // Marco simple
    for(int i=2; i<118; i++) { gotoXY_mod(i, 2); printf("%c", 205); gotoXY_mod(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_mod(2, i); printf("%c", 186); gotoXY_mod(118, i); printf("%c", 186); }
    
    color_mod(0x1E); // Amarillo
    gotoXY_mod(40, 4); printf("=== MODIFICAR DATOS DE EMPLEADO ===");

    color_mod(0x1F);
    gotoXY_mod(30, 6); printf("Ingrese Legajo a modificar: ");
    scanf("%d", &legajoBuscado);

    // Leemos secuencialmente
    while(fread(&r, sizeof(struct reg), 1, m) == 1) {
        if(r.legajo == legajoBuscado && r.activo == true) {
            encontrado = true;
            
            while(opcion != 0) {
                // Redibujamos marco y titulo
                color_mod(0x1F);
                for(int i=2; i<118; i++) { gotoXY_mod(i, 2); printf("%c", 205); gotoXY_mod(i, 28); printf("%c", 205); }
                for(int i=2; i<28; i++)  { gotoXY_mod(2, i); printf("%c", 186); gotoXY_mod(118, i); printf("%c", 186); }
                color_mod(0x1E);
                gotoXY_mod(40, 4); printf("=== EDITANDO LEGAJO %d ===", r.legajo);
                
                // Mostramos los datos limpios
                mostrarDatosActuales(r);
                
                // Pedimos opcion ABAJO
                color_mod(0x1B); // Cyan
                gotoXY_mod(30, 24); printf("Elija el campo a modificar (1-5):      ");
                gotoXY_mod(64, 24); // Ponemos el cursor justo despues
                scanf("%d", &opcion);
                
                if(opcion == 0) break;

                // --- LOGICA DE MODIFICACION CORREGIDA ---
                switch(opcion) {
                    case 1: // Nombre
                        limpiarZonaInput(); // Borra la pregunta de "Elija campo..."
                        color_mod(0x1F); 
                        printf("INGRESE NUEVO NOMBRE: ");
                        _flushall(); gets(r.nombreapell);
                        break;

                    case 2: { // Puesto (Menu Flotante)
                        // Los menús flotantes sí pueden ir a la derecha porque tapan lo de abajo
                        std::vector<std::string> lP = {"Playero", "Cajero", "Encargado", "Administrativo", "Seguridad"};
                        // Movemos el menú un poco más a la derecha (x=60) para que no choque
                        int s = mostrarSelectorFlotante("NUEVO PUESTO", lP, 60, 12);
                        if(s!=-1) strcpy(r.puesto, lP[s].c_str());
                        break;
                    }

                    case 3: { // Area (Menu Flotante)
                        std::vector<std::string> lA = {"Playa", "Tienda FULL", "Lubricentro", "Gerencia"};
                        int s = mostrarSelectorFlotante("NUEVA AREA", lA, 60, 14);
                        if(s!=-1) strcpy(r.area, lA[s].c_str());
                        break;
                    }

                    case 4: { // Turno (Menu Flotante)
                        std::vector<std::string> lT = {"Manana", "Tarde", "Noche"};
                        int s = mostrarSelectorFlotante("NUEVO TURNO", lT, 60, 16);
                        if(s!=-1) strcpy(r.turno, lT[s].c_str());
                        break;
                    }

                    case 5: // Sueldo
                        limpiarZonaInput(); // Borra la pregunta de abajo
                        color_mod(0x1F); 
                        printf("INGRESE NUEVO SUELDO: $");
                        scanf("%d", &r.sueldo);
                        break;
                }
                
                // GUARDADO
                fseek(m, -((long)sizeof(struct reg)), SEEK_CUR);
                fwrite(&r, sizeof(struct reg), 1, m);
                fseek(m, -((long)sizeof(struct reg)), SEEK_CUR);
                
                // Mensaje de exito
                color_mod(0x2F); // Verde
                gotoXY_mod(45, 26); printf(" CAMBIO GUARDADO CORRECTAMENTE ");
                Sleep(800); 
                gotoXY_mod(45, 26); printf("                               "); // Borrar mensaje
            }
            break; 
        }
    }

    if(!encontrado) {
        color_mod(0x4F);
        gotoXY_mod(30, 15); printf(" No se encontro el Legajo %d ", legajoBuscado);
        getch();
    }

    fclose(m);
}