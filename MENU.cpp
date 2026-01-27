#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // Para getch()
#include <windows.h> // Para colores y posicionar cursor

#include "MENU.h"

// Definimos las teclas
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13

// Función auxiliar para cambiar colores puntuales
// Color 31 = Fondo Azul (1), Letra Blanca (F) -> 0x1F
// Color 241 = Fondo Blanco (F), Letra Azul (1) -> 0xF1 (Para resaltar)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Función para ocultar el cursor parpadeante (queda más pro)
void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Función para dibujar el logo fijo
void dibujarLogo() {
    setColor(0x1F); // Azul YPF
    printf("\n");
    printf("  __   __  _____   _____ \n"); 
    printf("  \\ \\ / / |  __ \\ |  ___|\n");
    printf("   \\ V /  | |__) || |__  \n");
    printf("    | |   |  ___/ |  __| \n");
    printf("    | |   | |     | |    \n");
    printf("    |_|   |_|     |_|    \n");
    printf("\n");
    printf("=========================================================\n");
    printf("       SISTEMA DE GESTION DE PERSONAL - TFI 2026         \n");
    printf("=========================================================\n\n");
}

int mostrarMenuPrincipal() {
    // Lista de opciones exacta
    const char* opciones[] = {
        "1. Crear archivo (Reiniciar base de datos)",
        "2. Grabar informacion (Alta de Empleado)",
        "3. Baja Logica (Desactivar Empleado)",
        "4. Baja Fisica (Eliminar definitivamente)",
        "5. Modificacion de campos",
        "6. Listado de la informacion",
        "7. Consulta por clave (Legajo/DNI)",
        "8. Crear estructura dinamica (Cargar a RAM)",
        "9. Mostrar datos de la estructura dinamica",
        "0. Salir"
    };
    
    int nOpciones = 10; // Cantidad total de opciones
    int cursor = 0;     // Opción seleccionada actualmente (empieza en la primera)
    char tecla;
    
    // Configuración inicial de consola
    system("color 1F"); 
    ocultarCursor();

    while(1) {
        system("cls"); // Limpiar pantalla para redibujar
        dibujarLogo();

        // Bucle para dibujar las opciones
        for(int i = 0; i < nOpciones; i++) {
            if(i == cursor) {
                // Si es la opción donde estoy parado: RESALTAR
                setColor(0xF9); // Fondo Blanco, Letra Azul brillante
                printf("  >> %s <<  \n", opciones[i]);
            } else {
                // Opción normal
                setColor(0x1F); // Fondo Azul, Letra Blanca
                printf("     %s      \n", opciones[i]);
            }
        }
        
        // Resetear color
        setColor(0x1F);
        printf("\n=========================================================\n");
        printf("  Use las FLECHAS para mover y ENTER para seleccionar.");

        // Capturar tecla
        tecla = getch();

        if(tecla == -32 || tecla == 224) { // Código especial de flechas
            tecla = getch(); // Capturar el segundo código
            if(tecla == ARRIBA && cursor > 0) {
                cursor--;
            }
            if(tecla == ABAJO && cursor < nOpciones - 1) {
                cursor++;
            }
        } 
        else if(tecla == ENTER) {
            // RETORNAR EL VALOR CORRECTO PARA TU MAIN
            // El array va de 0 a 9.
            // Si elige cursor 0 ("1. Crear"), devolvemos 1.
            // Si elige cursor 9 ("0. Salir"), devolvemos 0.
            
            if (cursor == 9) return 0; // Opción Salir
            return cursor + 1;         // Opciones 1 a 9
        }
    }
}