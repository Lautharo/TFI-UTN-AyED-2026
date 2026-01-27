#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h> 
#include "MENU.h"
#include "SONIDO.h" // <--- IMPORTANTE: Incluimos tu modulo de sonido

// Definimos códigos de teclas
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

// Colores
#define COLOR_FONDO 0x1F  // Azul fondo, Letra blanca
#define COLOR_MARCO 0x1B  // Azul fondo, Letra Cyan
#define COLOR_RESALTADO 0xF1 // Blanco fondo, Letra Azul
#define COLOR_BARRA 0x9F  // Azul claro fondo, Letra blanca
#define COLOR_MUSICA_ON 0x2F // Verde fondo, Letra Blanca (Para el boton ON)
#define COLOR_MUSICA_OFF 0x4F // Rojo fondo, Letra Blanca (Para el boton OFF)

// --- HERRAMIENTAS DE CONSOLA ---

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int getAnchoConsola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// --- DIBUJO ---

// AHORA RECIBE EL ESTADO DE LA MUSICA PARA DIBUJAR EL CARTELITO
void dibujarBarraSuperior(int musicaActiva) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ancho = getAnchoConsola();
    
    // 1. Pintar fondo de la barra
    setColor(COLOR_BARRA); 
    gotoxy(0, 0);
    for(int i=0; i<ancho; i++) printf(" "); 

    // 2. Usuario (Izquierda)
    gotoxy(2, 0);
    printf("USUARIO: ADMINISTRADOR");

    // 3. ESTADO MUSICA (Centro) - NUEVO
    const char* txtMusicaOn =  " [M] MUSICA: ON  ";
    const char* txtMusicaOff = " [M] MUSICA: OFF ";
    int xMusica = (ancho / 2) - 8; // Centrado
    
    gotoxy(xMusica, 0);
    if(musicaActiva) {
        setColor(COLOR_MUSICA_ON); // Verde
        printf("%s", txtMusicaOn);
    } else {
        setColor(COLOR_MUSICA_OFF); // Rojo
        printf("%s", txtMusicaOff);
    }

    // 4. Fecha (Derecha)
    setColor(COLOR_BARRA); // Volver al color de la barra
    char fecha[30];
    sprintf(fecha, "FECHA: %02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    gotoxy(ancho - strlen(fecha) - 2, 0); 
    printf("%s", fecha);
}

void dibujarPiePagina() {
    int ancho = getAnchoConsola();
    int yPie = 29; 
    
    setColor(COLOR_BARRA);
    gotoxy(0, yPie);
    for(int i=0; i<ancho; i++) printf(" "); 
    
    const char* texto = "UTN FRT - TFI 2026 - GRUPO 11";
    int x = (ancho - strlen(texto)) / 2;
    
    gotoxy(x, yPie);
    printf("%s", texto);
}

void dibujarLogoYPF(int y) {
    int ancho = getAnchoConsola();
    int x = (ancho - 26) / 2; 
    
    setColor(COLOR_FONDO);
    gotoxy(x, y);   printf(" __   __  _____   _____ ");
    gotoxy(x, y+1); printf(" \\ \\ / / |  __ \\ |  ___|");
    gotoxy(x, y+2); printf("  \\ V /  | |__) || |__  ");
    gotoxy(x, y+3); printf("   | |   |  ___/ |  __| ");
    gotoxy(x, y+4); printf("   | |   | |     | |    ");
    gotoxy(x, y+5); printf("   |_|   |_|     |_|    ");
}

void dibujarCajaMenu(int yInicio) {
    int ancho = getAnchoConsola();
    int anchoCaja = 60;
    int altoCaja = 13;
    int x1 = (ancho - anchoCaja) / 2;
    int x2 = x1 + anchoCaja;
    int y2 = yInicio + altoCaja;
    int i;

    setColor(COLOR_MARCO); 

    for(i = x1; i <= x2; i++) { gotoxy(i, yInicio); printf("%c", 205); gotoxy(i, y2); printf("%c", 205); }
    for(i = yInicio; i <= y2; i++) { gotoxy(x1, i); printf("%c", 186); gotoxy(x2, i); printf("%c", 186); }
    gotoxy(x1, yInicio); printf("%c", 201); gotoxy(x2, yInicio); printf("%c", 187);
    gotoxy(x1, y2); printf("%c", 200); gotoxy(x2, y2); printf("%c", 188);
    
    const char* titulo = " MENU PRINCIPAL ";
    gotoxy(x1 + (anchoCaja - strlen(titulo))/2, yInicio);
    printf("%s", titulo);
}

// --- FUNCION PRINCIPAL ---

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
    int cursor = 0;
    char tecla;
    
    // VARIABLES DE ESTADO DE MUSICA
    static int musicaActiva = 1; // 1 = ON, 0 = OFF (Static para recordar si sales y vuelves)
    static int primeraVez = 1;   // Para arrancar la musica solo la primera vez que abris el programa
    
    if (primeraVez) {
        iniciarMusica();
        primeraVez = 0;
    }
    
    system("mode con: cols=120 lines=30");
    SetConsoleTitle("SISTEMA DE GESTION YPF"); 
    ocultarCursor();

    while(1) {
        setColor(COLOR_FONDO);
        system("cls");
        
        // Pasamos el estado de la musica para que se dibuje ROJO o VERDE
        dibujarBarraSuperior(musicaActiva);
        
        dibujarLogoYPF(3);
        dibujarCajaMenu(10); 
        dibujarPiePagina();

        int ancho = getAnchoConsola();
        for(int i = 0; i < nOpciones; i++) {
            int largoTexto = 40; 
            int xOpcion = (ancho - largoTexto) / 2;
            int yOpcion = 12 + i; 
            
            gotoxy(xOpcion, yOpcion);
            
            if(i == cursor) {
                setColor(COLOR_RESALTADO);
                printf(" >> %-30s << ", opciones[i]);
            } else {
                setColor(COLOR_FONDO);
                printf("    %-30s    ", opciones[i]);
            }
        }

        // Input
        tecla = getch();
        if(tecla == -32 || tecla == 224) { 
            tecla = getch(); 
            if(tecla == ARRIBA) {
                cursor = (cursor > 0) ? cursor - 1 : nOpciones - 1;
                Beep(750, 30); 
            }
            if(tecla == ABAJO) {
                cursor = (cursor < nOpciones - 1) ? cursor + 1 : 0;
                Beep(750, 30);
            }
        } 
        // --- LOGICA DEL BOTON 'M' ---
        else if (tecla == 'm' || tecla == 'M') {
            toggleMusica(&musicaActiva); // Cambia el estado y pausa/reanuda
            // Al terminar el if, el while da la vuelta y redibuja la barra con el color nuevo
        }
        else if(tecla == ENTER) {
            Beep(1000, 100); 
            setColor(0x07); 
            system("cls");
            
            if (cursor == 9) {
                detenerMusica(); // Apagar musica al salir del todo
                return 0;
            }
            return cursor + 1;
        }
    }
}