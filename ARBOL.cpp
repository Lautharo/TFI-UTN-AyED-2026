#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "CAMPOS.h"
#include "MENU.h" 
#include "ARBOL.h"

// --- HERRAMIENTAS VISUALES LOCALES ---
void gotoXY_arbol(int x, int y) {
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void color_arbol(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// --- LOGICA DEL ARBOL ---

// Crear un nodo nuevo
Nodo* crearNodo(reg r) {
    Nodo* nuevo = new Nodo(); 
    nuevo->dato = r;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// Insertar en el arbol (Ordenado por Legajo)
void insertarNodo(Nodo *&raiz, reg r) {
    if(raiz == NULL) {
        raiz = crearNodo(r);
    }
    else if(r.legajo < raiz->dato.legajo) {
        insertarNodo(raiz->izq, r); 
    }
    else {
        insertarNodo(raiz->der, r); 
    }
}

void borrarArbol(Nodo *raiz) {
    if(raiz != NULL) {
        borrarArbol(raiz->izq);
        borrarArbol(raiz->der);
        delete raiz;
    }
}

Nodo *raizGlobal = NULL; 


// --- CASO 8: CARGAR DESDE ARCHIVO ---
void cargarArbolEnMemoria() {
    FILE *m = fopen("campos.dat", "rb");
    reg r;
    int cont = 0;

    // CORRECCION AQUI: Color PRIMERO, luego CLS
    color_arbol(0x1F); // Azul
    system("cls");     // Ahora si se pinta todo el fondo
    
    // Marco simple
    for(int i=2; i<118; i++) { gotoXY_arbol(i, 2); printf("%c", 205); gotoXY_arbol(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_arbol(2, i); printf("%c", 186); gotoXY_arbol(118, i); printf("%c", 186); }
    gotoXY_arbol(2, 2); printf("%c", 201); gotoXY_arbol(118, 2); printf("%c", 187);
    gotoXY_arbol(2, 28); printf("%c", 200); gotoXY_arbol(118, 28); printf("%c", 188);

    color_arbol(0x1E); // Amarillo
    gotoXY_arbol(40, 5); printf("=== CARGANDO ESTRUCTURA DINAMICA (ARBOL) ===");

    if (m == NULL) {
        color_arbol(0x4F); // Rojo
        // (Opcional: si quisieras fondo rojo en error, harias cls aqui tmb)
        gotoXY_arbol(30, 10); printf("ERROR: No existe el archivo de datos.");
        getch();
        return;
    }

    if(raizGlobal != NULL) {
        borrarArbol(raizGlobal);
        raizGlobal = NULL;
    }

    gotoXY_arbol(40, 10); printf("Leyendo registros e insertando nodos...");
    
    color_arbol(0x1B); // Cyan
    gotoXY_arbol(40, 12); printf("[                                        ]");

    fread(&r, sizeof(struct reg), 1, m);
    while(!feof(m)) {
        if(r.activo) {
            insertarNodo(raizGlobal, r);
            cont++;
            
            if(cont % 2 == 0) { 
                gotoXY_arbol(41 + (cont%38), 12); printf("%c", 219); 
                Sleep(20); 
            }
        }
        fread(&r, sizeof(struct reg), 1, m);
    }
    
    fclose(m);

    color_arbol(0x1B);
    for(int i=0; i<40; i++) { gotoXY_arbol(41+i, 12); printf("%c", 219); }

    color_arbol(0x2F); // Verde
    gotoXY_arbol(35, 15); printf(" ESTRUCTURA CREADA EXITOSAMENTE EN RAM ");
    gotoXY_arbol(35, 17); printf(" Total de Nodos insertados: %d ", cont);
    
    color_arbol(0x9F);
    gotoXY_arbol(40, 26); printf("Presione una tecla para volver...");
    getch();
}


// --- HERRAMIENTAS VISUALIZACION ---

void dibujarEncabezadoArbol() {
    color_arbol(0x1F); 
    for(int i=3; i<118; i++) { gotoXY_arbol(i, 6); printf("%c", 205); gotoXY_arbol(i, 8); printf("%c", 205); } 
    gotoXY_arbol(2, 6); printf("%c", 204); gotoXY_arbol(2, 8); printf("%c", 204); 
    gotoXY_arbol(118, 6); printf("%c", 185); gotoXY_arbol(118, 8); printf("%c", 185); 
    
    color_arbol(0x1E); 
    gotoXY_arbol(4, 7);  printf("LEGAJO");
    gotoXY_arbol(15, 7); printf("NOMBRE Y APELLIDO");
    gotoXY_arbol(50, 7); printf("PUESTO");
    gotoXY_arbol(70, 7); printf("AREA");
    gotoXY_arbol(90, 7); printf("TURNO");
    gotoXY_arbol(105, 7); printf("SUELDO");
}

void inOrden(Nodo *raiz, int &y) {
    if(raiz != NULL) {
        inOrden(raiz->izq, y);
        
        if (y > 25) {
            color_arbol(0x1B); gotoXY_arbol(80, 26); printf("Siguiente pagina >>"); getch();
            color_arbol(0x1F); for(int j=9; j<=26; j++) { gotoXY_arbol(3, j); printf("                                                                                                                "); }
            y = 9; 
        }

        color_arbol(0x1F); 
        reg r = raiz->dato;
        
        gotoXY_arbol(4, y);  printf("%d", r.legajo);
        gotoXY_arbol(15, y); printf("%-30s", r.nombreapell); 
        gotoXY_arbol(50, y); printf("%-15s", r.puesto);
        gotoXY_arbol(70, y); printf("%-15s", r.area);
        gotoXY_arbol(90, y); printf("%-10s", r.turno);
        gotoXY_arbol(105, y); printf("$%d", r.sueldo);
        
        y++; 
        
        inOrden(raiz->der, y);
    }
}

// --- CASO 9: MOSTRAR ---
void mostrarArbolOrdenado() {
    if(raizGlobal == NULL) {
        // CORRECCION: Color rojo antes de borrar pantalla
        color_arbol(0x4F); 
        system("cls");
        printf("\n [ERROR]: El Arbol esta vacio.\n");
        printf(" Debe ejecutar primero la OPCION 8 para cargar los datos en memoria.\n");
        getch();
        return;
    }

    // CORRECCION AQUI TAMBIEN: Color Azul PRIMERO
    color_arbol(0x1F); 
    system("cls"); // Ahora al borrar, se llena de azul el fondo
    
    // Marco
    for(int i=2; i<118; i++) { gotoXY_arbol(i, 2); printf("%c", 205); gotoXY_arbol(i, 28); printf("%c", 205); }
    for(int i=2; i<28; i++)  { gotoXY_arbol(2, i); printf("%c", 186); gotoXY_arbol(118, i); printf("%c", 186); }
    gotoXY_arbol(2, 2); printf("%c", 201); gotoXY_arbol(118, 2); printf("%c", 187);
    gotoXY_arbol(2, 28); printf("%c", 200); gotoXY_arbol(118, 28); printf("%c", 188);

    color_arbol(0x1E);
    gotoXY_arbol(40, 4); printf("=== REPORTE ORDENADO POR LEGAJO (ARBOL BST) ===");
    
    dibujarEncabezadoArbol();

    int y = 9;
    inOrden(raizGlobal, y);

    const char* msj = "Presione una tecla para volver al Menu...";
    color_arbol(0x9F); 
    gotoXY_arbol((120 - strlen(msj))/2, 26); 
    if(y < 26) printf("%s", msj); else { gotoXY_arbol((120 - strlen(msj))/2, 28); printf("%s", msj); } 

    getch();
}