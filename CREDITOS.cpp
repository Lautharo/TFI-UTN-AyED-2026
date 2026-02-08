#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "CREDITOS.h"

// --- Herramientas visuales locales ---
void gotoXY_cred(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_cred(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void mostrarCreditos() {
    color_cred(0x1F);
	system("cls");
    

    // 1. DIBUJAR MARCO
    // Horizontales
    for(int i=2; i<118; i++) { 
        gotoXY_cred(i, 2); printf("%c", 205); 
        gotoXY_cred(i, 28); printf("%c", 205); 
    }
    // Verticales
    for(int i=2; i<28; i++) { 
        gotoXY_cred(2, i); printf("%c", 186); 
        gotoXY_cred(118, i); printf("%c", 186); 
    }
    // Esquinas
    gotoXY_cred(2, 2); printf("%c", 201); gotoXY_cred(118, 2); printf("%c", 187);
    gotoXY_cred(2, 28); printf("%c", 200); gotoXY_cred(118, 28); printf("%c", 188);

    // 2. TÍTULO
    color_cred(0x1E); // Amarillo
    gotoXY_cred(45, 4); printf("=== AUTORES DEL PROYECTO ===");

    color_cred(0x1B); // Cyan claro
    gotoXY_cred(48, 6); printf("UTN FRT - TFI 2025");

    // 3. LISTA DE INTEGRANTES
    color_cred(0x1F); // Blanco
    
    // Formato: Nombre a la izquierda (x=30), Legajo a la derecha (x=80)
    int y = 10;
    
    gotoXY_cred(30, y);   printf("1. Apas Thiago Lautaro");
    gotoXY_cred(80, y);   printf("[ Legajo: 64205 ]");
    
    y += 3; // Dejamos espacio entre nombres
    gotoXY_cred(30, y);   printf("2. Bustos Geronimo Francisco");
    gotoXY_cred(80, y);   printf("[ Legajo: 64269 ]");

    y += 3;
    gotoXY_cred(30, y);   printf("3. Fernandez Lautaro Luciano");
    gotoXY_cred(80, y);   printf("[ Legajo: 64453 ]");

    y += 3;
    gotoXY_cred(30, y);   printf("4. Novillo Daruich Lucca Joaquin");
    gotoXY_cred(80, y);   printf("[ Legajo: 64418 ]");

    // 4. PIE DE PÁGINA
    color_cred(0x9F); // Azul claro fondo
    const char* msj = "Presione una tecla para volver al Menu...";
    gotoXY_cred((120 - strlen(msj))/2, 26); 
    printf("%s", msj);

    getch();
}