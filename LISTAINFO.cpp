#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "CAMPOS.h"
#include "MENU.h" 

// --- HERRAMIENTAS VISUALES LOCALES ---
void gotoXY_lista(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_lista(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Funcion para dibujar el encabezado con bordes perfectos
void dibujarEncabezadoTabla() {
    color_lista(0x1F); // Azul fondo
    
    // Lineas horizontales (Centro)
    for(int i=3; i<118; i++) { 
        gotoXY_lista(i, 6); printf("%c", 205); 
        gotoXY_lista(i, 8); printf("%c", 205); 
    } 
    
    // UNIONES "T" (Para que conecte con el marco)
    gotoXY_lista(2, 6); printf("%c", 204); // ╠
    gotoXY_lista(2, 8); printf("%c", 204); // ╠
    gotoXY_lista(118, 6); printf("%c", 185); // ╣
    gotoXY_lista(118, 8); printf("%c", 185); // ╣
    
    // Titulos de columnas (Amarillo)
    color_lista(0x1E); 
    gotoXY_lista(4, 7);  printf("LEGAJO");
    gotoXY_lista(15, 7); printf("NOMBRE Y APELLIDO");
    gotoXY_lista(50, 7); printf("PUESTO");
    gotoXY_lista(70, 7); printf("AREA");
    gotoXY_lista(90, 7); printf("TURNO");
    gotoXY_lista(105, 7); printf("SUELDO");
}

void realizarListaInfo()
{
    struct reg r; 
    FILE *m;
    int cont = 0;
    int y = 9; 

    m = fopen("campos.dat", "rb");

    if (m == NULL) {
        system("cls");
        color_lista(0x4F); // Rojo error
        printf("\n [ERROR]: No se pudo abrir la base de datos 'campos.dat'.\n");
        getch();
        return;  
    }

    // --- INTERFAZ ---
    system("cls");
    color_lista(0x1F); // Fondo Azul global
    
    // Marco Principal
    for(int i=2; i<118; i++) { gotoXY_lista(i, 2); printf("%c", 205); gotoXY_lista(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_lista(2, i); printf("%c", 186); gotoXY_lista(118, i); printf("%c", 186); }
    gotoXY_lista(2, 2); printf("%c", 201); gotoXY_lista(118, 2); printf("%c", 187);
    gotoXY_lista(2, 28); printf("%c", 200); gotoXY_lista(118, 28); printf("%c", 188);

    // Titulo
    color_lista(0x1E); // Amarillo
    gotoXY_lista(45, 4); printf("=== NOMINA DE EMPLEADOS ===");
    
    dibujarEncabezadoTabla();

    // LEER DATOS
    fread(&r, sizeof(struct reg), 1, m);

    while (!feof(m))
    {
        if(r.activo == true) { 
            
            // Paginacion
            if (y > 25) {
                color_lista(0x1B);
                gotoXY_lista(80, 26); printf("Siguiente pagina >> (Presione tecla)");
                getch();
                
                color_lista(0x1F);
                for(int j=9; j<=26; j++) {
                    gotoXY_lista(3, j);
                    printf("                                                                                                                "); 
                }
                y = 9; 
            }

            // --- AQUI ESTABA EL CAMBIO ---
            // Antes alternabamos colores. Ahora forzamos BLANCO siempre.
            color_lista(0x1F); // Blanco Brillante sobre Azul
            
            gotoXY_lista(4, y);  printf("%d", r.legajo);
            gotoXY_lista(15, y); printf("%-30s", r.nombreapell); 
            gotoXY_lista(50, y); printf("%-15s", r.puesto);
            gotoXY_lista(70, y); printf("%-15s", r.area);
            gotoXY_lista(90, y); printf("%-10s", r.turno);
            gotoXY_lista(105, y); printf("$%d", r.sueldo);
            
            y++;    
            cont++; 
        }
        
        fread(&r, sizeof(struct reg), 1, m);
    }

    fclose(m);

    // Pie de pagina
    if (cont == 0) {
        color_lista(0x4F); 
        gotoXY_lista(40, 15); printf(" LA BASE DE DATOS ESTA VACIA O NO HAY ACTIVOS ");
    } else {
        color_lista(0x1B); // Cyan suave
        gotoXY_lista(4, 27); printf("Total Registros: %d", cont);
    }

    const char* msj = "Presione una tecla para volver al Menu...";
    color_lista(0x9F); // Celeste claro fondo
    gotoXY_lista((120 - strlen(msj))/2, 26); 
    if(y < 26) printf("%s", msj); 
    else { gotoXY_lista((120 - strlen(msj))/2, 28); printf("%s", msj); } 

    getch();
}