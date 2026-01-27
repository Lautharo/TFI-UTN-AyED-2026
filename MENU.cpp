#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h> 
#include "MENU.h"

// Definimos códigos de teclas
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

// --- HERRAMIENTAS GRAFICAS ---

// Cambiar colores (Fondo y Texto)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Mover el cursor a una posición X, Y
void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// Ocultar el cursor parpadeante (queda más profesional)
void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Dibujar una caja con bordes dobles
void dibujarCuadro(int x1, int y1, int x2, int y2) {
    int i;
    // Caracteres ASCII extendidos para bordes dobles
    char esqSI = 201, esqSD = 187, esqII = 200, esqID = 188;
    char lineaH = 205, lineaV = 186;

    setColor(0x1B); // Azul con bordes Celestes (Cyan)

    // Esquinas
    gotoxy(x1, y1); printf("%c", esqSI);
    gotoxy(x2, y1); printf("%c", esqSD);
    gotoxy(x1, y2); printf("%c", esqII);
    gotoxy(x2, y2); printf("%c", esqID);

    // Líneas Horizontales
    for(i = x1+1; i < x2; i++) {
        gotoxy(i, y1); printf("%c", lineaH);
        gotoxy(i, y2); printf("%c", lineaH);
    }

    // Líneas Verticales
    for(i = y1+1; i < y2; i++) {
        gotoxy(x1, i); printf("%c", lineaV);
        gotoxy(x2, i); printf("%c", lineaV);
    }
}

// Barra de estado inferior con fecha y hora
void barraEstado() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    // Dibujamos una franja abajo
    setColor(0x90); // Fondo Azul Claro (9), Letra Negra (0)
    gotoxy(0, 24); 
    // Rellenamos la linea
    for(int i=0; i<80; i++) printf(" ");
    
    gotoxy(2, 24); 
    printf(" USUARIO: ADMINISTRADOR | FECHA: %02d/%02d/%d | UTN FRT - TFI 2026", 
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// --- LOGICA DEL MENU ---

int mostrarMenuPrincipal() {
    const char* opciones[] = {
        "1. Crear archivo (Reiniciar DB)",
        "2. Grabar informacion (Alta)",
        "3. Baja Logica (Desactivar)",
        "4. Baja Fisica (Eliminar)",
        "5. Modificacion de campos",
        "6. Listado de la informacion",
        "7. Consulta por clave",
        "8. Estructura Dinamica (Cargar)",
        "9. Estructura Dinamica (Mostrar)",
        "0. Salir del Sistema"
    };
    
    int nOpciones = 10;
    int cursor = 0; // Donde empieza seleccionado
    char tecla;
    
    // Configuración Inicial
    system("color 1F"); // Fondo Azul YPF, Letra Blanca
    ocultarCursor();

    while(1) {
        // Redibujar pantalla solo lo necesario o limpiar
        // Para evitar parpadeo, limpiamos y redibujamos todo el frame
        system("cls"); 
        
        // 1. DIBUJAR MARCO PRINCIPAL (Centrado)
        dibujarCuadro(15, 2, 65, 21);
        
        // 2. DIBUJAR CABECERA DENTRO DEL MARCO
        setColor(0x1E); // Azul con letra Amarilla (E)
        gotoxy(32, 4); printf("SISTEMA YPF");
        gotoxy(32, 5); printf("-----------");

        // 3. DIBUJAR OPCIONES
        for(int i = 0; i < nOpciones; i++) {
            gotoxy(20, 7 + i); // Posicionar X=20, Y=7+i
            
            if(i == cursor) {
                // Opción SELECCIONADA: Invertir colores (Blanco fondo, Azul letra)
                setColor(0xF1); 
                printf(" >> %-35s << ", opciones[i]); 
            } else {
                // Opción NORMAL: Azul fondo, Blanca letra
                setColor(0x1F); 
                printf("    %-35s    ", opciones[i]);
            }
        }
        
        // 4. BARRA DE ESTADO
        barraEstado();

        // 5. CAPTURAR TECLA
        tecla = getch();

        if(tecla == -32 || tecla == 224) { // Código de flechas
            tecla = getch(); // Capturar dirección
            
            if(tecla == ARRIBA) {
                cursor--;
                if(cursor < 0) cursor = nOpciones - 1; // Vuelta completa abajo
                Beep(600, 20); // Sonido cortito
            }
            
            if(tecla == ABAJO) {
                cursor++;
                if(cursor >= nOpciones) cursor = 0; // Vuelta completa arriba
                Beep(600, 20); // Sonido cortito
            }
        } 
        else if(tecla == ENTER) {
            Beep(1000, 80); // Sonido de confirmación
            setColor(0x07); // Volver a color normal antes de salir
            system("cls");
            
            // Lógica para devolver el int correcto al MAIN
            // El array va de 0 a 9.
            // Si elige cursor 0 (Opción 1), devolvemos 1.
            // Si elige cursor 9 (Opción 0), devolvemos 0.
            if (cursor == 9) return 0;
            return cursor + 1;
        }
    }
}