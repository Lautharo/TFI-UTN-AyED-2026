#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h> 
#include "CAMPOS.h" // Necesario para la estructura 'reg'
#include "MENU.h"   // Necesario para los menús
#include "ALTA.h"

// --- HERRAMIENTAS LOCALES (Para mantener el estilo visual) ---
// Las repetimos aquí para asegurar que no falten referencias
void gotoXY_alta(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_alta(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void dibujarCampoAlta(int x, int y, const char* etiqueta) {
    color_alta(0x1F); // Azul fondo, Letra Blanca
    gotoXY_alta(x, y);
    printf("%s", etiqueta);
    color_alta(0x18); // Azul fondo, Letra Gris (campo vacio)
    printf(" .............................."); 
}

// --- FUNCION PRINCIPAL DE ALTA ---
void grabarInformacion()
{
    reg r;
    FILE *m;
    
    // *** DIFERENCIA CLAVE: "ab" (Append) en vez de "wb" ***
    // Esto agrega datos al final sin borrar lo que ya existe.
    m = fopen("campos.dat", "ab"); 
    
    char opcion = 's';
    
    if (m == NULL) {
        // Si falla al abrir en modo append, intentamos crear (wb)
        m = fopen("campos.dat", "wb");
        if (m == NULL) {
            printf("Error critico: No se puede acceder al archivo.");
            return;
        }
    }
    
    while (opcion == 's' || opcion == 'S')
    {
        system("cls");
        
        // 1. DIBUJAR MARCO GRANDE (Igual que en Campos.cpp)
        color_alta(0x1F);
        // Horizontales
        for(int i=2; i<118; i++) { gotoXY_alta(i, 2); printf("%c", 205); gotoXY_alta(i, 28); printf("%c", 205); }
        // Verticales
        for(int i=2; i<28; i++)  { gotoXY_alta(2, i); printf("%c", 186); gotoXY_alta(118, i); printf("%c", 186); }
        // Esquinas
        gotoXY_alta(2, 2); printf("%c", 201); gotoXY_alta(118, 2); printf("%c", 187);
        gotoXY_alta(2, 28); printf("%c", 200); gotoXY_alta(118, 28); printf("%c", 188);

        // 2. TITULO DISTINTIVO
        color_alta(0x1E); // Amarillo
        // Centramos el titulo
        const char* titulo = "=== ALTA DE NUEVO EMPLEADO (AGREGAR) ===";
        gotoXY_alta((120 - strlen(titulo))/2, 4); 
        printf("%s", titulo);
        
        // Subtitulo explicativo (Opcional, para aclarar funcionamiento)
        color_alta(0x1B); // Cyan suave
        gotoXY_alta(42, 5); printf("(Agregando al final de la base de datos)");
        
        // 3. DIBUJAR ETIQUETAS
        int c1 = 10, c2 = 50; 
        dibujarCampoAlta(c1, 7,  "Nombre y Apellido:");
        dibujarCampoAlta(c1, 10, "Legajo:           ");
        dibujarCampoAlta(c1, 13, "Edad:             ");
        dibujarCampoAlta(c1, 16, "Sueldo:           ");
        
        dibujarCampoAlta(c2, 7,  "Puesto:           ");
        dibujarCampoAlta(c2, 10, "Turno:            ");
        dibujarCampoAlta(c2, 13, "Sexo:             ");
        dibujarCampoAlta(c2, 16, "Area:             ");

        // 4. INPUT DE DATOS
        color_alta(0x1F); 
        
        // -- Nombre --
        gotoXY_alta(c1 + 19, 7); _flushall(); gets(r.nombreapell);

        // -- Legajo --
        gotoXY_alta(c1 + 19, 10); scanf("%d", &r.legajo);

        // -- Edad --
        gotoXY_alta(c1 + 19, 13); scanf("%d", &r.edad);

        // -- Sueldo --
        gotoXY_alta(c1 + 19, 16); scanf("%d", &r.sueldo);

        // -- PUESTO (MENU) --
        std::vector<std::string> lPuestos = {"Playero", "Cajero", "Encargado", "Administrativo", "Seguridad"};
        int sP = mostrarSelectorFlotante("SELECCIONE", lPuestos, c2 + 19, 7);
        color_alta(0x1E); gotoXY_alta(c2 + 19, 7);
        if(sP != -1) { printf("%s", lPuestos[sP].c_str()); strcpy(r.puesto, lPuestos[sP].c_str()); } 
        else { printf("Indefinido"); strcpy(r.puesto, "Indefinido"); }

        // -- TURNO (MENU) --
        std::vector<std::string> lTurnos = {"Manana", "Tarde", "Noche"};
        int sT = mostrarSelectorFlotante("SELECCIONE", lTurnos, c2 + 19, 10);
        color_alta(0x1E); gotoXY_alta(c2 + 19, 10);
        if(sT != -1) { printf("%s", lTurnos[sT].c_str()); strcpy(r.turno, lTurnos[sT].c_str()); }
        else { printf("Indefinido"); strcpy(r.turno, "Indefinido"); }

        // -- SEXO (MENU) --
        std::vector<std::string> lSexo = {"Masculino", "Femenino", "Otro"};
        int sS = mostrarSelectorFlotante("SELECCIONE", lSexo, c2 + 19, 13);
        color_alta(0x1E); gotoXY_alta(c2 + 19, 13);
        if(sS != -1) { printf("%s", lSexo[sS].c_str()); strcpy(r.sexo, lSexo[sS].c_str()); }
        else { printf("Indefinido"); strcpy(r.sexo, "Indefinido"); }

        // -- AREA (MENU) --
        std::vector<std::string> lAreas = {"Playa", "Tienda FULL", "Lubricentro", "Gerencia"};
        int sA = mostrarSelectorFlotante("SELECCIONE", lAreas, c2 + 19, 16);
        color_alta(0x1E); gotoXY_alta(c2 + 19, 16);
        if(sA != -1) { printf("%s", lAreas[sA].c_str()); strcpy(r.area, lAreas[sA].c_str()); }
        else { printf("Indefinido"); strcpy(r.area, "Indefinido"); }
    
        r.activo = true;
        fwrite(&r, sizeof(struct reg), 1, m);
        
        // --- PIE DE PAGINA ---
        const char* msjExito = " EMPLEADO AGREGADO EXITOSAMENTE ";
        int xExito = (120 - strlen(msjExito)) / 2;
        color_alta(0x2F); // Fondo verde
        gotoXY_alta(xExito, 22);
        printf("%s", msjExito);
        
        const char* msjPregunta = "Desea agregar otro? (s/n): ";
        int xPregunta = (120 - strlen(msjPregunta)) / 2;
        color_alta(0x1F); 
        gotoXY_alta(xPregunta, 24); 
        printf("%s", msjPregunta);
        
        opcion = getch();
    }
    
    fclose(m);
    
    // MENSAJE DE SALIDA AZUL (Estilo consistente)
    const char* msjSalida = "Presione una tecla para volver al Menu...";
    int xSalida = (120 - strlen(msjSalida)) / 2;
    color_alta(0x9F); 
    gotoXY_alta(xSalida, 26); 
    printf("%s", msjSalida);
    
    getch(); 
}