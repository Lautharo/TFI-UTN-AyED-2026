#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h> 
#include "CAMPOS.h"
#include "MENU.h" 

// --- HERRAMIENTAS LOCALES ---
void gotoXY_local(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_local(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void dibujarCampo(int x, int y, const char* etiqueta) {
    color_local(0x1F); 
    gotoXY_local(x, y);
    printf("%s", etiqueta);
    color_local(0x18); 
    printf(" .............................."); 
}

// --- FUNCION PRINCIPAL ---
void carga_empleados()
{
	reg r;
	FILE*m;
	m = fopen("campos.dat","wb"); 
	
	char opcion='s';
	
	if (m == NULL) {
        printf("Error: No se pudo crear el archivo.");
        return; 
    }
    
    while (opcion == 's'||opcion == 'S')
    {
        system("cls");
        
        // 1. DIBUJAR MARCO GRANDE
        color_local(0x1F);
        // Lineas horizontales
        for(int i=2; i<118; i++) { gotoXY_local(i, 2); printf("%c", 205); gotoXY_local(i, 28); printf("%c", 205); }
        // Lineas verticales
        for(int i=2; i<28; i++)  { gotoXY_local(2, i); printf("%c", 186); gotoXY_local(118, i); printf("%c", 186); }
        // Esquinas
        gotoXY_local(2, 2); printf("%c", 201); gotoXY_local(118, 2); printf("%c", 187);
        gotoXY_local(2, 28); printf("%c", 200); gotoXY_local(118, 28); printf("%c", 188);

        // Titulo
        color_local(0x1E); // Amarillo
        gotoXY_local(40, 4); printf("=== ALTA DE EMPLEADO (RESET DB) ===");
        
        // 2. DIBUJAR ETIQUETAS
        int col1 = 10; 
        int col2 = 50; 
        
        dibujarCampo(col1, 7,  "Nombre y Apellido:");
        dibujarCampo(col1, 10, "Legajo:           ");
        dibujarCampo(col1, 13, "Edad:             ");
        dibujarCampo(col1, 16, "Sueldo:           ");
        
        dibujarCampo(col2, 7,  "Puesto:           ");
        dibujarCampo(col2, 10, "Turno:            ");
        dibujarCampo(col2, 13, "Sexo:             ");
        dibujarCampo(col2, 16, "Area:             ");

        // 3. INPUT DE DATOS
        color_local(0x1F); 
        
        // -- Nombre --
        gotoXY_local(col1 + 19, 7); _flushall(); gets(r.nombreapell);

        // -- Legajo --
        gotoXY_local(col1 + 19, 10); scanf("%d", &r.legajo);

        // -- Edad --
        gotoXY_local(col1 + 19, 13); scanf("%d", &r.edad);

        // -- Sueldo --
        gotoXY_local(col1 + 19, 16); scanf("%d", &r.sueldo);

        // -- PUESTO (MENU) --
        vector<string> listaPuestos = {"Playero", "Cajero", "Encargado", "Administrativo", "Seguridad"};
        int selPuesto = mostrarSelectorFlotante("SELECCIONE", listaPuestos, col2 + 19, 7);
        color_local(0x1E); 
        gotoXY_local(col2 + 19, 7);
        if(selPuesto != -1) { printf("%s", listaPuestos[selPuesto].c_str()); strcpy(r.puesto, listaPuestos[selPuesto].c_str()); } 
        else { printf("Indefinido"); strcpy(r.puesto, "Indefinido"); }

        // -- TURNO (MENU) --
        vector<string> listaTurnos = {"Manana", "Tarde", "Noche"};
        int selTurno = mostrarSelectorFlotante("SELECCIONE", listaTurnos, col2 + 19, 10);
        color_local(0x1E);
        gotoXY_local(col2 + 19, 10);
        if(selTurno != -1) { printf("%s", listaTurnos[selTurno].c_str()); strcpy(r.turno, listaTurnos[selTurno].c_str()); }
        else { printf("Indefinido"); strcpy(r.turno, "Indefinido"); }

        // -- SEXO (MENU) --
        vector<string> listaSexo = {"Masculino", "Femenino", "Otro"};
        int selSexo = mostrarSelectorFlotante("SELECCIONE", listaSexo, col2 + 19, 13);
        color_local(0x1E);
        gotoXY_local(col2 + 19, 13);
        if(selSexo != -1) { printf("%s", listaSexo[selSexo].c_str()); strcpy(r.sexo, listaSexo[selSexo].c_str()); }
        else { printf("Indefinido"); strcpy(r.sexo, "Indefinido"); }

        // -- AREA (MENU) --
        vector<string> listaAreas = {"Playa", "Tienda FULL", "Lubricentro", "Gerencia"};
        int selArea = mostrarSelectorFlotante("SELECCIONE", listaAreas, col2 + 19, 16);
        color_local(0x1E);
        gotoXY_local(col2 + 19, 16);
        if(selArea != -1) { printf("%s", listaAreas[selArea].c_str()); strcpy(r.area, listaAreas[selArea].c_str()); }
        else { printf("Indefinido"); strcpy(r.area, "Indefinido"); }
    
        r.activo = true;
        fwrite(&r, sizeof(struct reg), 1, m);
        
        // --- PIE DE PAGINA (Mensajes de éxito y continuar) ---
        
        // 1. Mensaje de Guardado (Centrado)
        const char* msjExito = " REGISTRO GUARDADO EXITOSAMENTE ";
        int xExito = (120 - strlen(msjExito)) / 2;
        color_local(0x2F); // Fondo verde
        gotoXY_local(xExito, 22);
        printf("%s", msjExito);
        
        // 2. Pregunta de continuar (Centrado)
        const char* msjPregunta = "Desea ingresar otro? (s/n): ";
        int xPregunta = (120 - strlen(msjPregunta)) / 2;
        color_local(0x1F); // Fondo Azul
        gotoXY_local(xPregunta, 24);
        printf("%s", msjPregunta);
        
        // Input sin mostrar cursor feo
        opcion = getch();
    }
    
    fclose(m);
    
    // --- MENSAJE DE SALIDA PERSONALIZADO (Reemplaza al system pause) ---
    // Esto se ejecuta cuando pones 'n'
    const char* msjSalida = "Presione una tecla para volver al Menu...";
    int xSalida = (120 - strlen(msjSalida)) / 2;
    
    color_local(0x9F); // Azul claro para diferenciarlo un poco (o usa 0x1F si quieres igual)
    gotoXY_local(xSalida, 26); // Abajo de la pregunta anterior
    printf("%s", msjSalida);
    
    getch(); // Espera la tecla (PAUSA MANUAL)
}