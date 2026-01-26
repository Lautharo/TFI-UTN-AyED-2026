#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "MENU.h" // <--- CAMBIO IMPORTANTE: .h en lugar de .cpp

int main()
{
    // Llamamos a la función que está en el otro archivo
    int opcion = mostrarMenu(); 
    
    printf("\nSeleccionaste la opcion: %d", opcion);
    
    // Mensaje de prueba (tu print original)
    printf("\nGero gay"); 
    printf("\nLautaro gay");
    
    return 0;
}