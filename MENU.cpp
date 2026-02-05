#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h> 
#include "MENU.h"
#include "SONIDO.h" // <--- IMPORTANTE: Incluimos tu modulo de sonido
#include <vector>
#include <string>
#include <iostream>
using namespace std;

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

void dibujarCajaMenu(int yInicio, int altoCaja) { 
    int ancho = getAnchoConsola();
    int anchoCaja = 60;
    
    // IMPORTANTE: BORRA la linea que decia "int altoCaja = 13;"
    // porque ahora el tamaño viene de afuera (el parametro de arriba).
    
    int x1 = (ancho - anchoCaja) / 2;
    int x2 = x1 + anchoCaja;
    int y2 = yInicio + altoCaja; // Usa el alto variable
    int i;

    setColor(COLOR_MARCO); 

    // Dibujamos bordes (igual que antes)
    for(i = x1; i <= x2; i++) { gotoxy(i, yInicio); printf("%c", 205); gotoxy(i, y2); printf("%c", 205); }
    for(i = yInicio; i <= y2; i++) { gotoxy(x1, i); printf("%c", 186); gotoxy(x2, i); printf("%c", 186); }
    gotoxy(x1, yInicio); printf("%c", 201); gotoxy(x2, yInicio); printf("%c", 187);
    gotoxy(x1, y2); printf("%c", 200); gotoxy(x2, y2); printf("%c", 188);
    
    // Solo dibujamos el titulo si es el Menu Principal (alto fijo 13)
    // O puedes quitar el titulo de la caja para que sea generica
    if (altoCaja == 13) {
        const char* titulo = " MENU PRINCIPAL ";
        gotoxy(x1 + (anchoCaja - strlen(titulo))/2, yInicio);
        printf("%s", titulo);
    }
}

int mostrarSubMenu(string titulo, const vector<string> &opciones) {
    int cursor = 0;
    char tecla;
    int nOpciones = opciones.size(); // ¡El vector nos dice su tamaño solo!
    
    // Calculamos la altura de la caja dinámicamente
    int yInicioCaja = 10;
    int altoCaja = nOpciones + 4;

    ocultarCursor();

    while(1) {
        setColor(COLOR_FONDO);
        system("cls"); 
        
        // Dibujamos el entorno
        dibujarBarraSuperior(1); 
        dibujarLogoYPF(3);
        dibujarPiePagina();
        
        // Dibujamos la caja
        dibujarCajaMenu(yInicioCaja, altoCaja);
        
        // Titulo centrado
        int ancho = getAnchoConsola();
        int xTitulo = (ancho - titulo.length()) / 2;
        setColor(0x1E); // Amarillo
        gotoxy(xTitulo, yInicioCaja);
        printf(" %s ", titulo.c_str()); // .c_str() es necesario para printf

        // Dibujar Opciones desde el Vector
        for(int i = 0; i < nOpciones; i++) {
            int largoTexto = 40; 
            int xOpcion = (ancho - largoTexto) / 2;
            int yOpcion = yInicioCaja + 2 + i; 
            
            gotoxy(xOpcion, yOpcion);
            
            if(i == cursor) {
                setColor(COLOR_RESALTADO);
                // Accedemos al texto del vector con opciones[i]
                printf(" >> %-30s << ", opciones[i].c_str());
            } else {
                setColor(COLOR_FONDO);
                printf("    %-30s    ", opciones[i].c_str());
            }
        }

        // Control (Igual que siempre)
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
        else if(tecla == ENTER) {
            Beep(1000, 100);
            return cursor; // Devuelve 0, 1, 2...
        }
        else if(tecla == 27) return -1; // Escape
    }
}

// --- PANTALLA DE CARGA AMARILLA (ESTILO YPF) ---
void mostrarPantallaCarga(const char* texto) {
    ocultarCursor(); 
    setColor(COLOR_FONDO); 
    system("cls");
    
    // 1. Logo YPF
    dibujarLogoYPF(4);

    // 2. Marco de la Barra
    int ancho = getAnchoConsola();
    int anchoBarra = 40;
    int xBarra = (ancho - anchoBarra) / 2;
    int yBarra = 15;

    // Texto centrado
    setColor(0x1E); // Amarillo
    gotoxy((ancho - strlen(texto)) / 2, yBarra - 2); 
    printf("%s", texto);
    
    // Dibujo del marco
    setColor(COLOR_MARCO); 
    gotoxy(xBarra - 1, yBarra); printf("%c", 201); 
    gotoxy(xBarra + anchoBarra, yBarra); printf("%c", 187);
    gotoxy(xBarra - 1, yBarra + 2); printf("%c", 200); 
    gotoxy(xBarra + anchoBarra, yBarra + 2); printf("%c", 188);
    
    for(int i=0; i<anchoBarra; i++) { 
        gotoxy(xBarra+i, yBarra); printf("%c", 205); 
        gotoxy(xBarra+i, yBarra+2); printf("%c", 205); 
    }
    gotoxy(xBarra - 1, yBarra + 1); printf("%c", 186); 
    gotoxy(xBarra + anchoBarra, yBarra + 1); printf("%c", 186);

    // 3. Animacion Llenado
    setColor(0x1E); // Amarillo
    for(int i=0; i < anchoBarra; i++) {
        gotoxy(xBarra + i, yBarra + 1); 
        printf("%c", 219); 
        Sleep(20); // Velocidad
    }
    Sleep(200); // Pausa final
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
        dibujarCajaMenu(10, 13); 
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

// --- SELECTOR FLOTANTE (SIN BORRAR FONDO) ---
int mostrarSelectorFlotante(const char* titulo, const vector<string> &opciones, int x, int y) {
    int cursor = 0;
    char tecla;
    int nOpciones = opciones.size();
    
    // Configurar tamaño de la caja
    int anchoCaja = 40; 
    int altoCaja = nOpciones + 2;
    
    // 1. DIBUJAR MARCO DE LA CAJITA
    setColor(COLOR_MARCO);
    
    // Borde Superior
    gotoxy(x, y); printf("%c", 201); 
    for(int i=0; i<anchoCaja; i++) printf("%c", 205);
    printf("%c", 187);
    
    // Borde Inferior
    gotoxy(x, y + altoCaja + 1); printf("%c", 200); 
    for(int i=0; i<anchoCaja; i++) printf("%c", 205);
    printf("%c", 188);

    // Laterales
    for(int i=0; i < altoCaja; i++) {
        gotoxy(x, y + 1 + i); printf("%c", 186);
        gotoxy(x + anchoCaja + 1, y + 1 + i); printf("%c", 186);
    }
    
    // Titulo del selector
    setColor(0x1E); // Amarillo
    gotoxy(x + 2, y); printf(" %s ", titulo);

    ocultarCursor();

    while(1) {
        // 2. DIBUJAR OPCIONES
        for(int i = 0; i < nOpciones; i++) {
            gotoxy(x + 2, y + 1 + i); 
            
            if(i == cursor) {
                setColor(COLOR_RESALTADO); 
                printf(" >> %-32s << ", opciones[i].c_str());
            } else {
                setColor(COLOR_FONDO); 
                printf("    %-32s    ", opciones[i].c_str());
            }
        }

        // 3. CAPTURAR TECLAS
        tecla = getch();
        if(tecla == -32 || tecla == 224) { 
            tecla = getch(); 
            if(tecla == ARRIBA) {
                cursor = (cursor > 0) ? cursor - 1 : nOpciones - 1;
            }
            if(tecla == ABAJO) {
                cursor = (cursor < nOpciones - 1) ? cursor + 1 : 0;
            }
        } 
        else if(tecla == ENTER) {
            Beep(1000, 50);
            
            // 4. BORRAR LA CAJA ANTES DE IRSE (IMPORTANTE)
            setColor(COLOR_FONDO);
            for(int i=0; i <= altoCaja + 1; i++) {
                gotoxy(x, y + i);
                for(int j=0; j <= anchoCaja + 1; j++) printf(" ");
            }
            
            return cursor;
        }
    }
}

// --- PANTALLA DE SALIDA ---
void mostrarSalida() {
    ocultarCursor();
    setColor(COLOR_FONDO); // Azul
    system("cls");
    
    dibujarLogoYPF(5);
    
    int ancho = getAnchoConsola();
    
    // 1. Animacion "Guardando"
    setColor(0x1E); // Amarillo
    const char* msjGuardando = "GUARDANDO CAMBIOS EN LA BASE DE DATOS...";
    gotoxy((ancho - strlen(msjGuardando))/2, 14); 
    printf("%s", msjGuardando);
    
    // Barrita de progreso rapida
    setColor(0x1B); // Cyan
    int xBarra = (ancho - 20) / 2;
    gotoxy(xBarra, 16); 
    for(int i=0; i<20; i++) {
        printf("%c", 219); // Bloque solido
        Sleep(40); // Velocidad
    }
    
    Sleep(500); // Pequeña pausa
    
    // 2. Cartel de Despedida
    setColor(COLOR_FONDO); 
    system("cls");
    dibujarLogoYPF(4);
    
    // Dibujamos un marco elegante para el saludo
    int anchoCaja = 50;
    int xBox = (ancho - anchoCaja) / 2;
    int yBox = 13;
    
    setColor(COLOR_MARCO);
    // Borde superior
    gotoxy(xBox, yBox); printf("%c", 201); for(int i=0;i<anchoCaja-2;i++) printf("%c",205); printf("%c", 187);
    // Laterales
    gotoxy(xBox, yBox+1); printf("%c", 186); gotoxy(xBox+anchoCaja-1, yBox+1); printf("%c", 186);
    gotoxy(xBox, yBox+2); printf("%c", 186); gotoxy(xBox+anchoCaja-1, yBox+2); printf("%c", 186);
    gotoxy(xBox, yBox+3); printf("%c", 186); gotoxy(xBox+anchoCaja-1, yBox+3); printf("%c", 186);
    // Borde inferior
    gotoxy(xBox, yBox+4); printf("%c", 200); for(int i=0;i<anchoCaja-2;i++) printf("%c",205); printf("%c", 188);
    
    // Textos
    setColor(0x1F); // Blanco Brillante
    const char* txt1 = "GRACIAS POR UTILIZAR EL SISTEMA";
    gotoxy((ancho - strlen(txt1))/2, yBox+1); printf("%s", txt1);
    
    setColor(0x1E); // Amarillo
    const char* txt2 = "HASTA LUEGO";
    gotoxy((ancho - strlen(txt2))/2, yBox+3); printf("%s", txt2);
    
    dibujarPiePagina();
    
    Sleep(2000); // Esperar 2 segundos para que se lea
    
    // Volvemos a negro para entregar el control al sistema operativo limpiamente
    setColor(0x07); 
    system("cls");
}