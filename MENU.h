#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
using namespace std;

// --- FUNCIONES PRINCIPALES ---
int mostrarMenuPrincipal();

// --- HERRAMIENTAS VISUALES (Disponibles para CAMPOS, ALTA, etc) ---
// 1. Muestra un menu completo (borra pantalla)
int mostrarSubMenu(string titulo, const vector<string> &opciones);

// 2. Muestra la pantalla de carga amarilla (Estilo YPF)
void mostrarPantallaCarga(const char* texto);

// 3. Muestra el menu flotante que NO borra el fondo (Para formularios)
int mostrarSelectorFlotante(const char* titulo, const vector<string> &opciones, int x, int y);

// 4. Dibuja la caja azul (Marco)
void dibujarCajaMenu(int yInicio, int altoCaja);

void mostrarSalida();

void setUsuarioActual(const char* nombre);

#endif