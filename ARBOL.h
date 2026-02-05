#ifndef ARBOL_H
#define ARBOL_H
#include "CAMPOS.h" // Necesitamos saber que es un 'reg'

struct Nodo {
    reg dato;        // El empleado
    Nodo *izq;       // Brazo izquierdo (Menores)
    Nodo *der;       // Brazo derecho (Mayores)
};

// Funciones que llamaremos desde el Main
void cargarArbolEnMemoria(); // Caso 8
void mostrarArbolOrdenado(); // Caso 9

#endif