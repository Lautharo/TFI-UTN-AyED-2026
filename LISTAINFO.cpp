#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "CAMPOS.h" 

void realizarListaInfo()
{
    struct reg r; 
    FILE *m;
    int cont = 0;

    system("CLS");
    printf("=== LISTADO GENERAL DE EMPLEADOS ===\n\n");

   
    m = fopen("campos.dat", "rb");

   
    if (m == NULL)
    {
        printf("[ERROR]: No se pudo abrir el archivo 'campos.dat'.\n");
        printf("Causas probables:\n");
        printf(" - No has cargado ningun empleado aun.\n");
        printf(" - El archivo tiene otro nombre en la funcion de Alta.\n");
        printf("\nPresione una tecla para volver al menu...");
        getch();
        return;  
    }

   
    printf("%-10s %-25s %-5s %-10s %-15s\n", "LEGAJO", "NOMBRE", "EDAD", "SUELDO", "PUESTO");
    printf("--------------------------------------------------------------------------\n");

   
    fread(&r, sizeof(struct reg), 1, m);

    while (!feof(m))
    {
        printf("%-10d %-25s %-5d $%-9d %-15s\n", 
               r.legajo, 
               r.nombreapell, 
               r.edad, 
               r.sueldo, 
               r.puesto);
        
        cont++;

        fread(&r, sizeof(struct reg), 1, m);
    }

  
    fclose(m);

  
    if (cont == 0)
    {
        printf("\n[ATENCION]: El archivo existe pero esta VACIO.\n");
    }
    else
    {
        printf("\n--------------------------------------------------------------------------\n");
        printf("Se listaron %d registros.\n", cont);
    }

    printf("\nPresione una tecla para volver al menu...");
    getch();
}